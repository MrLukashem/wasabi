
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
    AudioDriver(const AConfiguration& config): m_config{config} {}
    virtual ~AudioDriver() = default;

    // TODO: recheck how a device gonna be passed to the function
    virtual std::optional<TrackHandle> createAsyncTrack(const AConfiguration& config,
        const TrackBufferReadyCallback callback);
    virtual void releaseTrack(const TrackHandle& trackHandle);
    virtual bool start(const TrackHandle& trackHandle);
    virtual bool stop(const TrackHandle& trackHandle);
    virtual bool pause(const TrackHandle& trackHandle);
protected:
    AConfiguration m_config;
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

