
#include "include/catch.hpp"

#include "DeviceCapabilitiesProviders.hpp"


namespace wasabi {
namespace tests {

TEST_CASE("Base test", "[DeviceCapabilitiesProviders]") {
    const auto capabilitiesProvider = audio::utils::makeDeviceCapabilitiesProvider();
    REQUIRE_FALSE(capabilitiesProvider == nullptr);
}

} // namespace tests
} // namespace wasabi
