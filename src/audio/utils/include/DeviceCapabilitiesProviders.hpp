
#pragma once

#include "DeviceCapabilities.hpp"

#include <functional>


namespace wasabi {
namespace audio {
namespace utils {

std::function<std::vector<DeviceCapabilities>()> makeDeviceCapabilitiesProvider();

} // namespace utils
} // namespace audio
} // namespace wasabi