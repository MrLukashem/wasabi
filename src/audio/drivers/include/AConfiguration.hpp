
#pragma once


namespace wasabi {
namespace audio {
namespace drivers {

struct AConfiguration
{
    enum class AudioFormat {
    };
    bool isResamplingAllowed = false;
    uint32_t numOfChannles;
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
