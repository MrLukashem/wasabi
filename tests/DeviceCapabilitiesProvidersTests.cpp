
#include "include/catch.hpp"

#include "DeviceCapabilitiesProviders.hpp"


#ifdef ALSA_SUPPORTED
#include <alsa/asoundlib.h>
#include <alsa/control.h>
#endif


#ifdef ALSA_SUPPORTED
void** getHints() {
    void** hints = nullptr;
    return snd_device_name_hint(-1, "pcm", &hints) < 0 ? nullptr : hints;
}

std::size_t getNumberOfDevices(void** hints) {
    std::size_t numOfDevices{};
    while (hints != nullptr) {
        numOfDevices++;
        hints++;
    }

    return numOfDevices;
}
#endif

namespace wasabi {
namespace tests {

TEST_CASE("Base test", "[DeviceCapabilitiesProviders]") {
    const auto capabilitiesProvider = audio::utils::makeDeviceCapabilitiesProvider();
    REQUIRE_FALSE(capabilitiesProvider == nullptr);

    #ifdef ALSA_SUPPORTED
    const auto capabilities = capabilitiesProvider();
    REQUIRE(capabilities.size() != getNumberOfDevices(getHints()));

    SECTION("Capabilities content") {
        abort();
    }
    #endif
}

} // namespace tests
} // namespace wasabi
