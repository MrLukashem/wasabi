
#ifdef ALSA_SUPPORTED

#include "AudioDriver.hpp"


struct _snd_pcm;
using snd_pcm_t = _snd_pcm;

namespace wasabi {
namespace audio {
namespace drivers {

class ASoundAudioDriver : public AudioDriver {
public:
    ASoundAudioDriver();
    ~ASoundAudioDriver() = default;

    // TODO: recheck how a device gonna be passed to the function
    std::optional<TrackHandle> createAsyncTrack(const AConfiguration& config,
        TrackBufferReadyCallback callback) override;
    void releaseTrack(const TrackHandle& trackHandle) {}
    bool start(const TrackHandle& trackHandle) override { return {}; }
    bool stop(const TrackHandle& trackHandle) override { return {}; }
    bool pause(const TrackHandle& trackHandle) override { return {}; }
    bool flush(const TrackHandle& trackHandle) override { return {}; }
private:
    // TODO: Rule of five here
    struct AudioTrack {
        snd_pcm_t* handle;
        TrackHandleBase userHandleBase;
    };

    std::vector<AudioTrack> m_tracks;
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

#endif
