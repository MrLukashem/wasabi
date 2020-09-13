
#include "ASoundAudioDriver.hpp"

//#ifdef ALSA_SUPPORTED

#include "BasicLogger.hpp"

#include <alsa/asoundlib.h>


namespace wasabi {
namespace audio {

namespace {
utils::BasicLogger logger{"ASoundAudioDriver"};
} // namespace anonymous

namespace drivers {

ASoundAudioDriver::ASoundAudioDriver() {
}

std::optional<TrackHandle> ASoundAudioDriver::createAsyncTrack(const AConfiguration& config,
    TrackBufferReadyCallback callback
) {
    AudioTrack track{nullptr, {}};
    if (snd_pcm_open(&track.handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        logger.error("snd_pcm_open failed");
        return {};
    }
    if (snd_pcm_set_params(track.handle, SND_PCM_FORMAT_U8, SND_PCM_ACCESS_RW_INTERLEAVED, 1, 48000,
        1, 500000) < 0) {
        return {};
    }

    unsigned char buffer[16*1024];
    for (int i = 0; i < 16; i++) {
        auto frames = snd_pcm_writei(track.handle, buffer, sizeof(buffer));
        if (frames < 0) {
            frames = snd_pcm_recover(track.handle, frames, 0);
        }
        if (frames < 0) {
            break;
        }
    }

    m_tracks.push_back(std::move(track));
    return std::addressof(m_tracks.back().userHandleBase);
}

} // namespace drivers
} // namespace audio
} // namespace wasabi

//#endif
