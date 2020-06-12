
#pragma once

#include "TrackHandle.hpp"

#include <string>


namespace wasabi {
namespace audio {
namespace drivers {

struct TrackData {
    TrackHandle trackHandle;
    std::size_t bufferSize;
    void const* buffer;
    /* data */
};


} // namespace drivers
} // namespace audio
} // namespace wasabi