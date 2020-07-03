
#include "AudioPlaybackStream.hpp"


namespace wasabi {
namespace audio {

using namespace base;

StateType IdlePlaybackState::start(const AudioStreamContext* masterContext) {
    return {};
}

StateType IdlePlaybackState::stop(const AudioStreamContext* masterContext) {
    return {};
}

StateType IdlePlaybackState::connect(
    const AudioStreamContext* masterContext,
    const drivers::TrackBufferReadyCallback) {
    return {};
}

StateType IdlePlaybackState::disconnect(const AudioStreamContext* masterContext) {
    return {};
}

StateType IdlePlaybackState::pause(const AudioStreamContext* masterContext) {
    return {};
}

StateType IdlePlaybackState::resume(const AudioStreamContext* masterContext) {
    return {};
}

StateType IdlePlaybackState::flush(const AudioStreamContext* masterContext) {
    return {};
}

} // namespace audio
} // namespace wasabi