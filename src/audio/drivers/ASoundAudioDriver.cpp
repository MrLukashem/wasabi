
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
bool isPauseSupported(snd_pcm_t* handle);

} // namespace anonymous

namespace drivers {

ASoundAudioDriver::ASoundAudioDriver() {
}

std::optional<TrackHandle> ASoundAudioDriver::createAsyncTrack(
    const AConfiguration& config,
    const base::AudioBuffer<std::byte>& clientBuffer,
    TrackBufferReadyCallback callback // TODO: by cref
) {
    auto track = makeTrack();

    if (snd_pcm_open(&track->handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        logger.error("snd_pcm_open failed");
        return {};
    }

    auto hwparams = prepareHardwareParams(track->handle, config);
    if (hwparams == nullptr || snd_pcm_hw_params(track->handle, hwparams) < 0) {
        logger.error("preparing hardware params failed");
        return {};
    }

    auto swparams = prepareSoftwareParams(track->handle, config);
    if (swparams == nullptr || snd_pcm_sw_params(track->handle, swparams) < 0) {
        logger.error("preparing software params failed");
        return {};
    }

    track->alsaAsyncCallback = [this] (auto* handler) {
        aslaAsyncCallback(handler);
    };
    if (snd_async_add_pcm_handler(&track->asyncHandler, track->handle,
        *track->alsaAsyncCallback.target<void(*)(snd_async_handler_t*)>(), nullptr) < 0
    ) {
        logger.error("registering async callback failed");
        return {};
    }

    track->userCallback = callback;
    track->trackUserData->buffer = clientBuffer;
    m_tracks.push_back(std::move(track));
    return std::addressof(m_tracks.back()->userHandleBase);
}

inline ASoundAudioDriver::AudioTrackUPtr ASoundAudioDriver::makeTrack() noexcept {
    return AudioTrackUPtr(new AudioTrack{}, [this] (auto* track) { releaseResourcesForTrack(track); });
}

void ASoundAudioDriver::releaseResourcesForTrack(AudioTrack* track) noexcept {
    if (track == nullptr) {
        return;
    }

    stop(std::addressof(track->userHandleBase));
    snd_pcm_close(track->handle);
    delete track;
}

void ASoundAudioDriver::releaseTrack(const TrackHandle& trackHandle) {
    m_tracks.erase(
        std::remove_if(m_tracks.begin(), m_tracks.end(),
        [trackHandle] (const auto& track) {
            return trackHandle == std::addressof(track->userHandleBase);
        }), m_tracks.end());
}

bool ASoundAudioDriver::start(const TrackHandle& trackHandle) const {
    const auto* track = findTrack(trackHandle);
    if (track == nullptr || snd_pcm_start(track->handle) < 0) {
        logger.warn("No track found. No one to started");
        return false;
    }

    return true;
}

bool ASoundAudioDriver::resume(const TrackHandle& trackHandle) {
    const auto* track = findTrack(trackHandle);
    if (track == nullptr) {
        logger.warn("No track found with id = {}", trackHandle);
        return false;
    }

    const int doResume = 0;
    // TODO: implement pause internal if there is not pause supported by alsa
    if (!isPauseSupported(track->handle) || snd_pcm_pause(track->handle, doResume) < 0) {
        logger.warn(
            "No resume supported by ALSA driver. Stopping the playback for track with id = {}",
            trackHandle);
        stop(trackHandle);
        return false;
    }

    return true;
}

bool ASoundAudioDriver::stop(const TrackHandle& trackHandle) {
    const auto* track = findTrack(trackHandle);
    if (track == nullptr || snd_pcm_drain(track->handle) < 0) {
        logger.warn("No track found. No one to stopped");
        return false;
    }

    return true;
}

bool ASoundAudioDriver::pause(const TrackHandle& trackHandle) {
    const auto* track = findTrack(trackHandle);
    if (track == nullptr) {
        logger.warn("No track found with id = {}", trackHandle);
        return false;
    }

    const int doPause = 1;
    // TODO: implement pause internal if there is not pause supported by alsa
    if (!isPauseSupported(track->handle) || snd_pcm_pause(track->handle, doPause) < 0) {
        logger.warn(
            "No pause supported by ALSA driver. Stopping the playback for track with id = {}",
            trackHandle);
        stop(trackHandle);
        return false;
    }

    return true;
}

bool ASoundAudioDriver::flush(const TrackHandle& trackHandle) {
    const auto* track = findTrack(trackHandle);
    if (track == nullptr || snd_pcm_reset(track->handle) < 0) {
        logger.warn("No track found or cannot flush the track");
        return false;
    }

    return true;
}

const ASoundAudioDriver::AudioTrack* ASoundAudioDriver::findTrack(const TrackHandle& trackHandle
) const noexcept {
    auto trackItr = std::find_if(m_tracks.begin(), m_tracks.end(), [trackHandle] (const auto& track) {
        return trackHandle == std::addressof(track->userHandleBase);
    });

    return trackItr != m_tracks.end() ? (*trackItr).get() : nullptr;
}

const ASoundAudioDriver::AudioTrack* ASoundAudioDriver::findTrack(const snd_pcm_t* handle
) const noexcept {
    auto trackItr = std::find_if(m_tracks.begin(), m_tracks.end(), [handle] (const auto& track) {
        return handle == track->handle;
    });

    return trackItr != m_tracks.end() ? (*trackItr).get() : nullptr;
}

bool ASoundAudioDriver::doRevoveryAction(const ASoundAudioDriver::AudioTrack* track) const noexcept {
    if (snd_pcm_prepare(track->handle) < 0) {
        logger.error("The stream recovery action failed");
        return false;
    }

    return true;
}

void ASoundAudioDriver::aslaAsyncCallback(snd_async_handler_t* asyncHandler) noexcept {
    auto* pcmHandle = snd_async_handler_get_pcm(asyncHandler);
    const auto* track = findTrack(pcmHandle);
    if (track == nullptr) {
        logger.warn("No track found for async alsa callback. Closing pcm_handle");
        snd_pcm_close(pcmHandle);
        return;
    }

    void* data = snd_async_handler_get_callback_private(asyncHandler);
    if (data == nullptr && !doRevoveryAction(track)) {
        return;
    }

    auto* userData = static_cast<TrackData*>(data);
    track->userCallback(*userData);

    const auto availFramesToWrite = snd_pcm_avail_update(track->handle);
    const auto framesToWrite = availFramesToWrite < userData->buffer.length()
        ? userData->buffer.length() : availFramesToWrite;

    snd_pcm_writei(track->handle, userData->buffer.data(), framesToWrite);
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

bool isPauseSupported(snd_pcm_t* handle) {
    snd_pcm_hw_params_t* hwParams{};
    return snd_pcm_hw_params_current(handle, hwParams) == 0
        && snd_pcm_hw_params_can_pause(hwParams) == 0;
}

} // namespace anonymous
} // namespace audio
} // namespace wasabi

#endif
