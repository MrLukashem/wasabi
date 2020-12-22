
#pragma once

#include <string>
#include <vector>

#include "AudioTypes.hpp"


namespace wasabi {
namespace audio {

struct DeviceCapabilities {
    std::string name;
    std::vector<base::SampleRate> sampleRates;
    std::vector<base::BitDepth> bitDepths;
};

} // namespace audio
} // namespace wasabi
