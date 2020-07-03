
#pragma once

#include "AudioTypes.hpp"
#include "TrackHandle.hpp"


namespace wasabi {
namespace audio {
namespace drivers {

struct TrackData {
    TrackHandle trackHandle;
    std::size_t bufferSize;
    base::Channels numOfChannels;
    base::BitDepth bitDepth;
    void const* buffer;
    /* data */
};


} // namespace drivers
} // namespace audio
} // namespace wasabi