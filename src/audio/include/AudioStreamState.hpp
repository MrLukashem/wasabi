
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
    virtual StateType start(AudioStreamContext* const masterContext) = 0;
    virtual StateType stop(AudioStreamContext* const masterContext) = 0;
    virtual StateType connect(
        AudioStreamContext* const masterContext,
        const drivers::TrackBufferReadyCallback) = 0;
    virtual StateType disconnect(AudioStreamContext* const masterContext) = 0;
    virtual StateType pause(AudioStreamContext* const masterContext) = 0;
    virtual StateType resume(AudioStreamContext* const masterContext) = 0;
    virtual StateType flush(AudioStreamContext* const masterContext) = 0;
};

template <typename State>
struct DefaultPlaybackState : public AudioStreamState {
    StateType start(AudioStreamContext* const masterContext) override {
        return State::stateType;
    }
    StateType stop(AudioStreamContext* const masterContext) override {
        return State::stateType;
    }
    StateType connect(
        AudioStreamContext* const masterContext,
        const drivers::TrackBufferReadyCallback) {
        return State::stateType;
    }
    StateType disconnect(AudioStreamContext* const masterContext) override {
        return State::stateType;
    }
    StateType pause(AudioStreamContext* const masterContext) override {
        return State::stateType;
    }
    StateType resume(AudioStreamContext* const masterContext) override {
        return State::stateType;
    }
    StateType flush(AudioStreamContext* const masterContext) override {
        return State::stateType;
    }
};

struct IdlePlaybackState : DefaultPlaybackState<IdlePlaybackState> {
public:
    static constexpr StateType stateType = StateType::Idle;

    StateType connect(
        AudioStreamContext* masterContext,
        const drivers::TrackBufferReadyCallback) override;
};

} // namespace base
} // namespace audio
} // namespace wasabi