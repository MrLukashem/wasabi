
#pragma once

#include "AudioDriver.hpp"
#include "AudioStream.hpp"


namespace wasabi {
namespace audio {

template <typename SampleType>
class AudioPlaybackStream : public AudioStream<SampleType> {
public:
    AudioPlaybackStream() = default;
    AudioPlaybackStream(std::unique_ptr<AudioDriver> driver)
        : m_driver{std::move(driver)} {}

    void start() override {
    }

    void stop() override {
    }

    void connect(BufferReadyCallback<SampleType> callback) override {
    }
private:
    std::unique_ptr<AudioDriver> m_driver;
};

} // namespace audio
} // namespace wasabi
