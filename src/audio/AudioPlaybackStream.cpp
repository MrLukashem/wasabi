
#include "AudioPlaybackStream.hpp"

#include "AudioDriver.hpp"
#include "BasicLogger.hpp"


namespace wasabi::audio {

namespace {
utils::BasicLogger logger("AudioPlaybackStream");
} //anymouns namespace

using namespace base;

// IdlePlaybackState
StateType IdlePlaybackState::connect(AudioStreamContext* const masterContext,
    const drivers::TrackBufferReadyCallback callback) {
    const auto& trackHandleOpt = masterContext->getDriver()->createAsyncTrack(
        static_cast<drivers::AConfiguration>(masterContext->getConfiguration()), callback);

    if (!trackHandleOpt) {
        logger.critical("createAsyncTrack failed. Switching to Idle state");
        return StateType::Idle;
    }

    masterContext->setTrackHandle(*trackHandleOpt);
    return StateType::Connected;
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

StateType ConnectedPlaybackState::disconnect(AudioStreamContext* const masterContext) {
    const auto& trackHandleOpt = masterContext->getTrackHandle();
    if (trackHandleOpt) {
        masterContext->getDriver()->releaseTrack(*trackHandleOpt);
    }

    return StateType::Idle;
}

// RunningPlaybackState
StateType RunningPlaybackState::connect(AudioStreamContext* const masterContext,
    const drivers::TrackBufferReadyCallback callback
) {
    const auto& oldTrackHandleOpt = masterContext->getTrackHandle();
    if (oldTrackHandleOpt) {
        masterContext->getDriver()->stop(*oldTrackHandleOpt);
        masterContext->getDriver()->releaseTrack(*oldTrackHandleOpt);
        masterContext->resetTrackHandle();
    }

    const auto& trackHandleOpt = masterContext->getDriver()->createAsyncTrack(
        static_cast<drivers::AConfiguration>(masterContext->getConfiguration()), callback);
    if (!trackHandleOpt) {
        logger.critical("createAsyncTrack failed. Switching to Idle state");
        return StateType::Idle;
    }

    masterContext->setTrackHandle(*trackHandleOpt);
    return StateType::Connected;
}

StateType RunningPlaybackState::disconnect(AudioStreamContext* const masterContext) {
    const auto& trackHandleOpt = masterContext->getTrackHandle();
    if (trackHandleOpt) {
        masterContext->getDriver()->releaseTrack(*trackHandleOpt);
    }

    masterContext->resetTrackHandle();
    return StateType::Idle;
}

StateType RunningPlaybackState::stop(AudioStreamContext* const masterContext) {
    const auto& trackHandleOpt = masterContext->getTrackHandle();
    if (!trackHandleOpt) {
        logger.critical("No track handle in RunningState. Switching to Idle state");
        return StateType::Idle;
    }

    if (!masterContext->getDriver()->stop(*trackHandleOpt)) {
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
        masterContext->getDriver()->releaseTrack(*trackHandleOpt);
        masterContext->resetTrackHandle();
        return StateType::Idle;
    }

    return StateType::Connected;
}

} // namespace wasabi::audio
