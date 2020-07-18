
#pragma once

#include "AConfiguration.hpp"
#include "TrackData.hpp"

#include <optional>
#include <string>
#include <memory>
#include <functional>


namespace wasabi {
namespace audio {
namespace drivers {

using TrackBufferReadyCallback = std::function<void(std::shared_ptr<TrackData>)>;

class AudioDriver {
public:
    AudioDriver() = default;
    virtual ~AudioDriver() = default;

    // TODO: recheck how a device gonna be passed to the function
    virtual std::optional<TrackHandle> createAsyncTrack(const AConfiguration& config,
        const TrackBufferReadyCallback callback) = 0;
    virtual void releaseTrack(const TrackHandle& trackHandle) = 0;
    virtual bool start(const TrackHandle& trackHandle) = 0;
    virtual bool stop(const TrackHandle& trackHandle) = 0;
    virtual bool pause(const TrackHandle& trackHandle) = 0;
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

