
#pragma once

#include "AudioDriver.hpp"


namespace wasabi {
namespace audio {

struct AudioStreamContext;

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
    virtual StateType start(const AudioStreamContext* masterContext) = 0;
    virtual StateType stop(const AudioStreamContext* masterContext) = 0;
    virtual StateType connect(
        const AudioStreamContext* masterContext,
        const drivers::TrackBufferReadyCallback) = 0;
    virtual StateType disconnect(const AudioStreamContext* masterContext) = 0;
    virtual StateType pause(const AudioStreamContext* masterContext) = 0;
    virtual StateType resume(const AudioStreamContext* masterContext) = 0;
    virtual StateType flush(const AudioStreamContext* masterContext) = 0;
};

class IdlePlaybackState : public AudioStreamState {
public:
    StateType start(const AudioStreamContext* masterContext) override;
    StateType stop(const AudioStreamContext* masterContext) override;
    StateType connect(
        const AudioStreamContext* masterContext,
        const drivers::TrackBufferReadyCallback);
    StateType disconnect(const AudioStreamContext* masterContext) override;
    StateType pause(const AudioStreamContext* masterContext) override;
    StateType resume(const AudioStreamContext* masterContext) override;
    StateType flush(const AudioStreamContext* masterContext) override;

};

} // namespace base
} // namespace audio
} // namespace wasabi