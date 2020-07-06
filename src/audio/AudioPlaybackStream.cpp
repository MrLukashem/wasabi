
#include "AudioPlaybackStream.hpp"


namespace wasabi {
namespace audio {

using namespace base;

StateType IdlePlaybackState::connect(AudioStreamContext* const masterContext,
    const drivers::TrackBufferReadyCallback callback) {
    const auto trackHandle = masterContext->getDriver()->createAsyncTrack(
        static_cast<drivers::AConfiguration>(masterContext->getConfiguration()), callback);
    if (!trackHandle) {
        return StateType::Idle;
    }

    masterContext->setTrackHandle(*trackHandle);
    return StateType::Connected;
}

} // namespace audio
} // namespace wasabi