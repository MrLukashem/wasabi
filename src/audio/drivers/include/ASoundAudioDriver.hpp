
#ifdef ALSA_SUPPORTED

#include "AudioBuffer.hpp"
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

    // TODO: recheck how a device gonna be passed to the function
    std::optional<TrackHandle> createAsyncTrack(
        const AConfiguration& config,
        const base::AudioBuffer<std::byte>& clientBuffer,
        TrackBufferReadyCallback callback) override;
    void releaseTrack(const TrackHandle& trackHandle);
    bool start(const TrackHandle& trackHandle) const override;
    bool resume(const TrackHandle& trackHadle) override;
    bool stop(const TrackHandle& trackHandle) override;
    bool pause(const TrackHandle& trackHandle) override;
    bool flush(const TrackHandle& trackHandle) override;
private:
    struct AudioTrack {
        snd_pcm_t* handle;
        snd_async_handler_t* asyncHandler;
        TrackHandleBase userHandleBase;
        std::function<void(snd_async_handler_t*)> alsaAsyncCallback;
        TrackBufferReadyCallback userCallback;
        std::shared_ptr<TrackData> trackUserData;
    };
    using AudioTrackUPtr = std::unique_ptr<AudioTrack, std::function<void(AudioTrack*)>>;

    inline AudioTrackUPtr makeTrack() noexcept;
    void releaseResourcesForTrack(AudioTrack* track) noexcept;
    const AudioTrack* findTrack(const TrackHandle& trackHandle) const noexcept;
    const AudioTrack* findTrack(const snd_pcm_t* handle) const noexcept;

    bool doRevoveryAction(const AudioTrack* track) const noexcept;
    void aslaAsyncCallback(snd_async_handler_t* asyncHandler) noexcept;

    std::vector<AudioTrackUPtr> m_tracks;
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

#endif
