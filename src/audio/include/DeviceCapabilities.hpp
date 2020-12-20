
#pragma once

#include <string>
#include <vector>

#include "AudioTypes.hpp"


namespace wasabi {
namespace audio {

struct DeviceCapabilities {
    const std::string name;
    const std::vector<base::SampleRate> sampleRates;
    const std::vector<base::BitDepth> bitDepths;
};

} // namespace audio
} // namespace wasabi