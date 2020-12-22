
#include "DeviceCapabilitiesProviders.hpp"

#ifdef ALSA_SUPPORTED
#include <alsa/asoundlib.h>
#include <alsa/control.h>
#endif
#include <iostream>


namespace wasabi {
namespace audio {
namespace utils {

namespace {

DeviceCapabilities buildDeviceCapabilitiesFromHint(void* hint) {
    return {snd_device_name_get_hint(hint, "NAME"), {}, {}};
}

std::size_t sizeOfHintsArray(void** hints) {
    std::size_t size{};
    while (hints != nullptr) {
        size++;
        hints++;
    }

    return size;
}

} // namespace

std::function<std::vector<DeviceCapabilities>()> makeDeviceCapabilitiesProvider() {
    #ifdef ALSA_SUPPORTED
    void** hints = nullptr;
    const auto err = snd_device_name_hint(-1, "pcm", &hints);
    if (err < 0) {
        return {};
    }

    const auto hintsArraySize = sizeOfHintsArray(hints);
    std::vector<DeviceCapabilities> capabilitiesVec{hintsArraySize};
    std::transform(hints, hints + hintsArraySize, std::begin(capabilitiesVec), [] (auto& hint) {
        return buildDeviceCapabilitiesFromHint(hint);
    });
    
    snd_device_name_free_hint(hints);
    #endif

    return {};
}

} // namespace utils
} // namespace audio
} // namespace wasabi
