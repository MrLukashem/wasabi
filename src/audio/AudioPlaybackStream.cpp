
#include "AudioPlaybackStream.hpp"

#include "AudioDriver.hpp"
#include "BasicLogger.hpp"


namespace wasabi::audio {

using namespace base;

namespace {

utils::BasicLogger logger("AudioPlaybackStream");

StateType doConnect(
    AudioStreamContext* const masterContext, const drivers::TrackBufferReadyCallback callback) {
    const auto& trackHandleOpt = masterContext->getDriver()->createAsyncTrack(
        static_cast<drivers::AConfiguration>(masterContext->getConfiguration()), callback);

    if (!trackHandleOpt) {
        logger.error("createAsyncTrack failed. Switching to Idle state");
        return StateType::Idle;
    }

    masterContext->setTrackHandle(*trackHandleOpt);
    return StateType::Connected;
}

StateType doDisconnect(AudioStreamContext* const masterContext) {
    const auto& trackHandleOpt = masterContext->getTrackHandle();
    if (trackHandleOpt) {
        logger.info("Releasing the current track");
        masterContext->getDriver()->releaseTrack(*trackHandleOpt);
    }

    masterContext->resetTrackHandle();
    return StateType::Idle;
}

} //anymouns namespace

// IdlePlaybackState
StateType IdlePlaybackState::connect(AudioStreamContext* const masterContext,
    const drivers::TrackBufferReadyCallback callback
) {
    return doConnect(masterContext, callback);
}

// ConnectedPlaybackState
StateType ConnectedPlaybackState::start(AudioStreamContext* const masterContext) {
    const auto& trackHandleOpt = masterContext->getTrackHandle();
    if (!trackHandleOpt) {
        logger.critical("No track handle in ConnectedState. Switching to Idle state");
        return StateType::Idle;
    }

    if (!masterContext->getDriver()->start(*trackHandleOpt)) {
        logger.error("Start failed. Please reconfigure the stream or restart once again");
        return StateType::Connected;
    }

    return StateType::Running;
}

StateType ConnectedPlaybackState::connect(AudioStreamContext* const masterContext,
    const drivers::TrackBufferReadyCallback callback
) {
    ConnectedPlaybackState::disconnect(masterContext);
    return doConnect(masterContext, callback);
}

StateType ConnectedPlaybackState::disconnect(AudioStreamContext* const masterContext) {
    return doDisconnect(masterContext);
}

// RunningPlaybackState
StateType RunningPlaybackState::connect(AudioStreamContext* const masterContext,
    const drivers::TrackBufferReadyCallback callback
) {
    const auto& oldTrackHandleOpt = masterContext->getTrackHandle();
    if (oldTrackHandleOpt) {
        masterContext->getDriver()->stop(*oldTrackHandleOpt);
        doDisconnect(masterContext);
    }

    return doConnect(masterContext, callback);
}

StateType RunningPlaybackState::disconnect(AudioStreamContext* const masterContext) {
    return doDisconnect(masterContext);
}

StateType RunningPlaybackState::stop(AudioStreamContext* const masterContext) {
    const auto& trackHandleOpt = masterContext->getTrackHandle();
    if (!trackHandleOpt) {
        logger.critical("No track handle in RunningState. Switching to Idle state");
        return StateType::Idle;
    }

    if (!masterContext->getDriver()->stop(*trackHandleOpt)) {
        logger.error("Stop failed. Releasing track and returning to IdleState");
        return disconnect(masterContext);
    }

    return StateType::Connected;
}

StateType RunningPlaybackState::pause(AudioStreamContext* const masterContext) {
    const auto& trackHandleOpt = masterContext->getTrackHandle();
    if (!trackHandleOpt) {
        logger.critical("No track handle in RunningState. Switching to Idle state");
        return StateType::Idle;
    }

    if (!masterContext->getDriver()->pause(*trackHandleOpt)) {
        logger.error("Pause failed. Releasing track and returning to IdleState");
        return doDisconnect(masterContext);
    }

    return StateType::Connected;
}

} // namespace wasabi::audio
