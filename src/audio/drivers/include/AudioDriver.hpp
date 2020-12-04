
#pragma once

#include "AudioBuffer.hpp"
#include "AConfiguration.hpp"
#include "TrackData.hpp"

#include <optional>
#include <string>
#include <memory>
#include <functional>


namespace wasabi {
namespace audio {
namespace drivers {

using TrackBufferReadyCallback = std::function<void(TrackData&)>;

class AudioDriver {
public:
    AudioDriver() = default;
    virtual ~AudioDriver() = default;
    AudioDriver(AudioDriver&&) = default;
    AudioDriver& operator=(AudioDriver&&) = default;
    AudioDriver(const AudioDriver&) = delete;
    AudioDriver& operator=(const AudioDriver&) = delete;

    // TODO: recheck how a device gonna be passed to the function
    virtual std::optional<TrackHandle> createAsyncTrack(
        const AConfiguration& config,
        const base::AudioBuffer<std::byte>& clientBuffer,
        const TrackBufferReadyCallback callback) = 0;
    virtual void releaseTrack(const TrackHandle& trackHandle) = 0;
    virtual bool start(const TrackHandle& trackHandle) const = 0;
    virtual bool resume(const TrackHandle& trackHadle) = 0;
    virtual bool stop(const TrackHandle& trackHandle) = 0;
    virtual bool pause(const TrackHandle& trackHandle) = 0;
    virtual bool flush(const TrackHandle& trackHandle) = 0;
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

