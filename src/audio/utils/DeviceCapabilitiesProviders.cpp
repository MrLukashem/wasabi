
#include "DeviceCapabilitiesProviders.hpp"


namespace wasabi {
namespace audio {
namespace utils {

std::function<std::vector<DeviceCapabilities>()> makeDeviceCapabilitiesProvider() {
    return {};
}

} // namespace utils
} // namespace audio
} // namespace wasabi