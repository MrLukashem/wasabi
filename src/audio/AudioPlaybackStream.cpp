
#include "AudioPlaybackStream.hpp"

#include "AudioDriver.hpp"


namespace wasabi::audio {

using namespace base;

// IdlePlaybackState
StateType IdlePlaybackState::connect(AudioStreamContext* const masterContext,
    const drivers::TrackBufferReadyCallback callback) {
    const auto& trackHandleOpt = masterContext->getDriver()->createAsyncTrack(
        static_cast<drivers::AConfiguration>(masterContext->getConfiguration()), callback);

    if (!trackHandleOpt) {
        return StateType::Idle;
    }

    masterContext->setTrackHandle(*trackHandleOpt);
    return StateType::Connected;
}

// ConnectedPlaybackState
StateType ConnectedPlaybackState::start(AudioStreamContext* const masterContext) {
    const auto& trackHandleOpt = masterContext->getTrackHandle();
    if (!trackHandleOpt) {
        return StateType::Idle;
    }

    if (!masterContext->getDriver()->start(*trackHandleOpt)) {
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
    const bool isStopped = masterContext->getDriver()->stop(*oldTrackHandleOpt);
    masterContext->getDriver()->releaseTrack(*oldTrackHandleOpt);
    masterContext->resetTrackHandle();

    if (!isStopped) {
        return StateType::Idle;
    }

    const auto& trackHandleOpt = masterContext->getDriver()->createAsyncTrack(
        static_cast<drivers::AConfiguration>(masterContext->getConfiguration()), callback);
    if (!trackHandleOpt) {
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
        // TODO: to think how to handle no track found case.
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
        // TODO: to think how to handle no track found case.
        return StateType::Idle;
    }

    if (!masterContext->getDriver()->pause(*trackHandleOpt)) {
        masterContext->getDriver()->releaseTrack(*trackHandleOpt);
        masterContext->resetTrackHandle();
        return StateType::Idle;
    }

    return StateType::Connected;
}

} // namespace wasabi::audio
