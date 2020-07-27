
#pragma once

#include "AudioStream.hpp"


namespace wasabi {
namespace audio {

template <typename SampleType>
class AudioCaptureStream : public AudioStream<SampleType> {
public:
    void start() override {
    }

    void stop() override {
    }

    void connect(BufferReadyCallback<SampleType> callback) override {
    }
};

} // namespace audio
} // namespace wasabi