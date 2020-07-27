
#pragma once

#include "gmock/gmock.h"

#include "AudioDriver.hpp"


namespace wasabi::tests::mocks {

struct AudioDriverMock : audio::drivers::AudioDriver {
    MOCK_METHOD2(createAsyncTrack, std::optional<audio::drivers::TrackHandle>(
        const audio::drivers::AConfiguration&, const audio::drivers::TrackBufferReadyCallback));
    MOCK_METHOD1(releaseTrack, void(const audio::drivers::TrackHandle&));
    MOCK_METHOD1(start, bool(const audio::drivers::TrackHandle&));
    MOCK_METHOD1(stop, bool(const audio::drivers::TrackHandle&));
    MOCK_METHOD1(pause, bool(const audio::drivers::TrackHandle&));
    MOCK_METHOD1(flush, bool(const audio::drivers::TrackHandle&));
};

} // namespace wasabi::tests::mocks
