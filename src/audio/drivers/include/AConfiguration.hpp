
#pragma once

#include <stdint.h>


namespace wasabi {
namespace audio {
namespace drivers {

struct AConfiguration
{
    enum class AudioFormat {
    };

    bool isResamplingAllowed;
    uint32_t numOfChannels;
    uint32_t rate;
    AudioFormat format;
    // TODO: implementation od the structure
    bool operator==(const AConfiguration& rhs) const {
        return true;
    }
    /* data */
};


} // namespace drivers
} // namespace audio
} // namespace drivers
