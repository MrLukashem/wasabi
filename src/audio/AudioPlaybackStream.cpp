
#include "AudioPlaybackStream.hpp"


namespace wasabi {
namespace audio {

using namespace base;

StateType IdlePlaybackState::start() {
    return {};
}

StateType IdlePlaybackState::stop() {
    return {};
}

StateType IdlePlaybackState::connect(const drivers::TrackBufferReadyCallback) {
    return {};
}

StateType IdlePlaybackState::pause() {
    return {};
}

StateType IdlePlaybackState::resume() {
    return {};
}

StateType IdlePlaybackState::flush() {
    return {};
}

} // namespace audio
} // namespace wasabi