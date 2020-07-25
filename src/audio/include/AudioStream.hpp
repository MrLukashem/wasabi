
#pragma once

#include <functional>

#include "AudioBuffer.hpp"
#include "AudioStreamState.hpp"

namespace wasabi {
namespace audio {

template <typename SampleType>
using BufferReadyCallback = std::function<void(base::AudioBuffer<SampleType>&)>;

template <typename SampleType>
class AudioStream {
public:
    AudioStream() = default;
    virtual ~AudioStream() = default;

    virtual inline bool operator==(const base::StateType state) const {
        return getState() == state;
    }

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    virtual void flush() = 0;
    virtual void connect(const BufferReadyCallback<SampleType> callback) = 0;
    virtual void disconnect() = 0;
    virtual base::StateType getState() const = 0;
};

} // namespace audio
} // namespace wasabi
