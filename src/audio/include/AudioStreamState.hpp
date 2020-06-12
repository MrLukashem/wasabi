
#pragma once

#include "AudioDriver.hpp"


namespace wasabi {
namespace audio {
namespace base {

enum class StateType : uint8_t {
    Idle,
    Connected,
    Running,
    Paused,
    Stopped,
};

struct AudioStreamState {
    AudioStreamState() = default;
    virtual ~AudioStreamState() = default;
    virtual StateType start() = 0;
    virtual StateType stop() = 0;
    virtual StateType connect(const drivers::TrackBufferReadyCallback) = 0;
    virtual StateType pause() = 0;
    virtual StateType resume() = 0;
    virtual StateType flush() = 0;
};

class IdlePlaybackState : public AudioStreamState {
public:
    StateType start() override;
    StateType stop() override;
    StateType connect(const drivers::TrackBufferReadyCallback);
    StateType pause() override;
    StateType resume() override;
    StateType flush() override;
};

} // namespace base
} // namespace audio
} // namespace wasabi