
#ifdef ALSA_SUPPORTED

#include "AudioDriver.hpp"


struct _snd_pcm;
using snd_pcm_t = _snd_pcm;
struct _snd_async_handler;
using snd_async_handler_t = _snd_async_handler;

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
    void releaseTrack(const TrackHandle& trackHandle);
    bool start(const TrackHandle& trackHandle) const override;
    bool stop(const TrackHandle& trackHandle) override;
    bool pause(const TrackHandle& trackHandle) override;
    bool flush(const TrackHandle& trackHandle) override;
private:
    struct AudioTrack {
        snd_pcm_t* handle;
        snd_async_handler_t* ayncHandler;
        TrackHandleBase userHandleBase;
        std::shared_ptr<TrackData> trackUserData;
        std::function<void(snd_async_handler_t*)> alsaAsyncCallback;
    };

    const AudioTrack* findTrack(const TrackHandle& trackHandle) const noexcept;

    std::vector<AudioTrack> m_tracks;
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

#endif
