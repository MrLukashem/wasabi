
#pragma once

#include <functional>

#include "AudioBuffer.hpp"


namespace wasabi {
namespace audio {

template <typename SampleType>
using BufferReadyCallback = std::function<void(base::AudioBuffer<SampleType>&)>;

template <typename SampleType>
class AudioStream {
public:
    AudioStream() = default;
    virtual ~AudioStream() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void connect(BufferReadyCallback<SampleType> callback) = 0;
};

} // namespace audio
} // namespace wasabi
