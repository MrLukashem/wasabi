
#include "include/catch.hpp"

#include "AudioPlaybackStream.hpp"
#include "AudioDriverMock.hpp"


namespace wasabi {

using namespace audio::base;
using audio::AudioPlaybackStream;
using audio::AStreamConfiguration;
using audio::drivers::TrackHandle;
using namespace testing;

namespace tests {

std::shared_ptr<mocks::AudioDriverMock> driverMock =
    std::shared_ptr<mocks::AudioDriverMock>();

TEST_CASE("[AudioPlaybackStream] init", "Init") {
    AStreamConfiguration config{};
    auto stream = std::make_unique<AudioPlaybackStream<uint32_t>>(config, driverMock);
}

TEST_CASE("[AudioPlaybackStream] connect", "connect") {
    AStreamConfiguration config{};
    auto stream = std::make_unique<AudioPlaybackStream<uint32_t>>(config, driverMock);
    stream->connect([] (auto& buffer) { });

    EXPECT_CALL(*driverMock, createAsyncTrack(_, _)).WillOnce(Return(TrackHandle{}));
    REQUIRE(stream->getState() == StateType::Connected);
}

TEST_CASE("[AudioPlaybackStream] start", "start") {
    AStreamConfiguration config{};
    auto stream = std::make_unique<AudioPlaybackStream<uint32_t>>(config, driverMock);
    stream->connect([] (auto& buffer) { });

    EXPECT_CALL(*driverMock, createAsyncTrack(_, _)).WillOnce(Return(TrackHandle{}));

    stream->start();
    REQUIRE(stream->getState() == StateType::Running);
}
} // namespace tests
} // namespace wasabi