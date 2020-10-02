
#include "ASoundAudioDriver.hpp"

#ifdef ALSA_SUPPORTED

#include "BasicLogger.hpp"

#include <alsa/asoundlib.h>

#include <algorithm>
#include <functional>


namespace wasabi {
namespace audio {

namespace {

utils::BasicLogger logger{"ASoundAudioDriver"};

snd_pcm_hw_params_t* prepareHardwareParams(snd_pcm_t*, const drivers::AConfiguration&);
snd_pcm_sw_params_t* prepareSoftwareParams(snd_pcm_t*, const drivers::AConfiguration&);

// TODO: implement the function
snd_pcm_format_t toAlsaFormat(const drivers::AConfiguration::AudioFormat format) {
    return SND_PCM_FORMAT_U16;
}

} // namespace anonymous

namespace drivers {

ASoundAudioDriver::ASoundAudioDriver() {
}

std::optional<TrackHandle> ASoundAudioDriver::createAsyncTrack(const AConfiguration& config,
    TrackBufferReadyCallback callback
) {
    AudioTrack track{};

    if (snd_pcm_open(&track.handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        logger.error("snd_pcm_open failed");
        return {};
    }

    auto hwparams = prepareHardwareParams(track.handle, config);
    if (hwparams == nullptr || snd_pcm_hw_params(track.handle, hwparams) < 0) {
        logger.error("preparing hardware params failed");
        return {};
    }

    auto swparams = prepareSoftwareParams(track.handle, config);
    if (swparams == nullptr || snd_pcm_sw_params(track.handle, swparams) < 0) {
        logger.error("preparing software params failed");
        return {};
    }

    snd_async_handler_t* asyncHandler = nullptr;
    track.alsaAsyncCallback = [] (auto* handler) {};
    if (snd_async_add_pcm_handler(&asyncHandler, track.handle,
        *track.alsaAsyncCallback.target<void(*)(snd_async_handler_t*)>(), nullptr) < 0
    ) {
        logger.error("registering async callback failed");
        return {};
    }

    m_tracks.push_back(std::move(track));
    return std::addressof(m_tracks.back().userHandleBase);
}

void ASoundAudioDriver::releaseTrack(const TrackHandle& trackHandle) {
    logger.info("removing track");
    m_tracks.erase(
        std::remove_if(m_tracks.begin(), m_tracks.end(),
        [trackHandle] (const auto& track) {
            return trackHandle == std::addressof(track.userHandleBase);
        }), m_tracks.end());
}

bool ASoundAudioDriver::start(const TrackHandle& trackHandle) const {
    const auto* track = findTrack(trackHandle);
    if (track == nullptr || snd_pcm_start(track->handle) < 0) {
        logger.warn("No track found. No one started.");
        return false;
    }

    return true;
}

bool ASoundAudioDriver::stop(const TrackHandle& trackHandle) {
    return false;
}

bool ASoundAudioDriver::pause(const TrackHandle& trackHandle) {
    return false;
}

bool ASoundAudioDriver::flush(const TrackHandle& trackHandle) {
    return false;
}

const ASoundAudioDriver::AudioTrack* ASoundAudioDriver::findTrack(
    const TrackHandle& trackHandle
) const noexcept {
    auto trackItr = std::find_if(m_tracks.begin(), m_tracks.end(), [trackHandle] (const auto& track) {
        return trackHandle == std::addressof(track.userHandleBase);
    });

    return trackItr != m_tracks.end() ? &(*trackItr) : nullptr;
}

} // namespace drivers

namespace {

snd_pcm_hw_params_t* prepareHardwareParams(
    snd_pcm_t* handle,
    const drivers::AConfiguration& config
) {
    snd_pcm_hw_params_t* params{};
    snd_pcm_hw_params_alloca(&params);

    if (snd_pcm_hw_params_any(handle, params) < 0) {
        logger.error("snd_pcm_hw_params_any failed");
        return nullptr;
    }

    if (snd_pcm_hw_params_set_rate_resample(
        handle, params, static_cast<uint32_t>(config.isResamplingAllowed))
    ) {
        logger.error("Set allowed resampling to "
            + std::to_string(config.isResamplingAllowed) + "failed");
        return nullptr;
    }

    if (snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED)) {
        logger.error("snd_pcm_hw_params_set_access failed");
        return nullptr;
    }

    if (snd_pcm_hw_params_set_format(handle, params, toAlsaFormat(config.format))) {
        logger.error("Set audio format failed");
        return nullptr;
    }

    if (snd_pcm_hw_params_set_channels(handle, params, config.numOfChannels)) {
        logger.error("Set number of channles = " + std::to_string(config.numOfChannels) + "failed");
        return nullptr;
    }

    uint32_t targetRate = config.rate;
    if (snd_pcm_hw_params_set_rate_near(handle, params, &targetRate, nullptr)) {
        logger.error("Setting sample rate failed");
        return nullptr;
    }
    if (targetRate != config.rate) {
        logger.error("target rate differ then allowed by alsa driver failed");
        return nullptr;
    }

    return params;
}

snd_pcm_sw_params_t* prepareSoftwareParams(
    snd_pcm_t* handle,
    const drivers::AConfiguration& config
) {
    snd_pcm_sw_params_t* params{};
    snd_pcm_sw_params_alloca(&params);
    return params;
}

} // namespace anonymous
} // namespace audio
} // namespace wasabi

#endif
