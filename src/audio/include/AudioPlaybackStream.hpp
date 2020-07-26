
#pragma once

#include "AudioStream.hpp"
#include "AStreamConfiguration.hpp"
#include "Exceptions.hpp"
#include "TrackHandle.hpp"

#include <memory>


namespace wasabi::audio {

namespace drivers {
class AudioDriver;
} // namespace drivers

using base::StateType;

struct AudioStreamContext {
    AudioStreamContext() = default;
    virtual ~AudioStreamContext() = default;

    virtual drivers::AudioDriver* getDriver() const noexcept = 0;
    virtual AStreamConfiguration getConfiguration() const noexcept = 0;
    virtual std::optional<drivers::TrackHandle> getTrackHandle() const noexcept = 0;
    virtual void resetTrackHandle() noexcept = 0;
    virtual void setTrackHandle(const drivers::TrackHandle& trackHandle) noexcept = 0;
};

template <typename SampleType>
class AudioPlaybackStream : public AudioStream<SampleType>, public AudioStreamContext {
public:
    // TODO: temporary for tests. Remove asap
    AudioPlaybackStream() = default;
    AudioPlaybackStream(
        const AStreamConfiguration config,
        std::shared_ptr<drivers::AudioDriver> driver
    ): m_config{config}, m_driver{driver}, m_trackHandle{} {
        m_clientBuffer = base::AudioBuffer<SampleType>(
            m_config.m_bufferSize, m_config.m_channels.m_value);

        changeState(base::StateType::Idle);
    }
    virtual ~AudioPlaybackStream() = default;

    void start() override {
        changeState(m_currentState->start(this));
    }

    void stop() override {
        changeState(m_currentState->stop(this));
    }

    void connect(const BufferReadyCallback<SampleType> callback) override {
        changeState(m_currentState->connect(this, [this, callback] (auto trackData) {
            callback(m_clientBuffer);
        }));
    }

    void pause() override {
        changeState(m_currentState->pause(this));
    }

    void flush() override {
        changeState(m_currentState->flush(this));
    }

    void disconnect() override {
        changeState(m_currentState->disconnect(this));
    }

    base::StateType getState() const override {
        return m_currentState->getMyState();
    }

    /*
        AudioStreamContext interface
    */
    drivers::AudioDriver* getDriver() const noexcept override {
        return m_driver.get();
    }

    AStreamConfiguration getConfiguration() const noexcept override {
        return m_config;
    }

    std::optional<drivers::TrackHandle> getTrackHandle() const noexcept override {
        return m_trackHandle;
    }

    void resetTrackHandle() noexcept {
        m_trackHandle = {};
    }

    void setTrackHandle(const drivers::TrackHandle& trackHandle) noexcept override {
        m_trackHandle = trackHandle;
    }
protected:
    void changeState(const base::StateType newState) {
        switch (newState) {
        case base::StateType::Idle:
            m_currentState = std::make_unique<base::IdlePlaybackState>();
            break;
        case base::StateType::Connected:
            m_currentState = std::make_unique<base::ConnectedPlaybackState>();
            break;
        case base::StateType::Running:
            m_currentState = std::make_unique<base::RunningPlaybackState>();
            break;
        default:
            m_currentState = std::make_unique<base::IdlePlaybackState>();
            throw base::StateException{"Unregognized state. Internal wasabi error."};
        }
    }
private:
    const AStreamConfiguration m_config{};
    const std::shared_ptr<drivers::AudioDriver> m_driver;
    std::unique_ptr<base::AudioStreamState> m_currentState;
    base::AudioBuffer<SampleType> m_clientBuffer;
    std::optional<drivers::TrackHandle> m_trackHandle;
};

} // namespace wasabi::audio
