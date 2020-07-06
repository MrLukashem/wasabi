
#ifdef ALSA_SUPPORTED

#include "AudioDriver.hpp"


namespace wasabi {
namespace audio {
namespace drivers {

class ASoundAudioDriver : public AudioDriver {
public:
    ASoundAudioDriver(const AConfiguration& config);
    virtual ~ASoundAudioDriver() = default;

    // TODO: recheck how a device gonna be passed to the function
    std::optional<TrackHandle> createAsyncTrack(const AConfiguration& config,
        TrackBufferReadyCallback callback) { return {};}
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

#endif