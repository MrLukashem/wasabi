
#pragma once

#include "AudioStream.hpp"
#include "AudioStreamState.hpp"
#include "Exceptions.hpp"

#include <memory>

// TODO: forward declaration of AudioDriver
namespace wasabi {
namespace audio {

template <typename SampleType>
class AudioPlaybackStream : public AudioStream<SampleType> {
public:
    // TODO: temporary for tests. Remove asap
    AudioPlaybackStream() = default;
    AudioPlaybackStream(std::shared_ptr<drivers::AudioDriver> driver): m_driver{driver} {
        changeState(base::StateType::Idle);
    }

    void start() override {
        changeState(m_currentState->start());
    }

    void stop() override {
        changeState(m_currentState->stop());
    }

    void connect(const BufferReadyCallback<SampleType> callback) override {
        const auto trackBufferReady = [this] (auto trackData) {
        };
        changeState(m_currentState->connect(trackBufferReady));
    }

    void pause() override {}
    void resume() override {}
    void flush() override {}
    void disconnect() override {}
protected:
    void changeState(const base::StateType newState) {
        switch (newState) {
        case base::StateType::Idle:
            m_currentState = std::make_unique<base::IdlePlaybackState>();
            break;
        case base::StateType::Connected:
            break;
        case base::StateType::Running:
            break;
        case base::StateType::Paused:
            break;
        case base::StateType::Stopped:
            break;
        default:
            m_currentState = std::make_unique<base::IdlePlaybackState>();
            throw base::StateException{"Unregognized state. Internal wasabi error."};
            break;
        }
    }
private:
    const std::shared_ptr<drivers::AudioDriver> m_driver;
    std::unique_ptr<base::AudioStreamState> m_currentState;
};

} // namespace audio
} // namespace wasabi
