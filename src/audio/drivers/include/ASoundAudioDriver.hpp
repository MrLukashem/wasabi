
#ifdef ALSA_SUPPORTED

#include "AudioDriver.hpp"


namespace wasabi {
namespace audio {
namespace drivers {

class ASoundAudioDriver : public AudioDriver {
public:
    ASoundAudioDriver(const AConfiguration& config);
    virtual ~ASoundAudioDriver() = default;
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

#endif