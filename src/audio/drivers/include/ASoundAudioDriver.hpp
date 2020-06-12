
#ifdef ALSA_SUPPORTED

#include "AudioDriver.hpp"


namespace wasabi {
namespace audio {
namespace drivers {

class ASoundAudioDriver : public AudioDriver {
public:
    ASoundAudioDriver(const AConfiguration& config);
    virtual ~ASoundAudioDriver() = default;

    bool setNewAConfiguration(const AConfiguration& config) { return {}; }
    // TODO: recheck how a device gonna be passed to the function
    TrackHandle createAsyncTrack(const std::string& deviceName,
        TrackBufferReadyCallback callback) { return {};}
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

#endif