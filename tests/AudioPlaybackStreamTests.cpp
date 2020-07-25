
#include "include/catch.hpp"

#include "AudioPlaybackStream.hpp"
#include "AudioDriverMock.hpp"


namespace wasabi {

using namespace testing;
using namespace audio::base;
using audio::AudioPlaybackStream;
using audio::AStreamConfiguration;
using audio::drivers::TrackHandle;
using audio::drivers::TrackHandleBase;

namespace tests {

MATCHER_P(TrackHandleMatcher, trackHandle, "") {
    return arg == trackHandle;
}

MATCHER_P(ConfigMatcher, audioStreamConfig, "") {
    return static_cast<audio::drivers::AConfiguration>(audioStreamConfig) == arg;
}

struct AudioTrackMock : TrackHandleBase { };

struct TestContext {
    TrackHandle generateTrackHandle() {
        handles.push_back(std::make_unique<AudioTrackMock>());
        return handles.back().get();
    }

    AStreamConfiguration config{};
    std::shared_ptr<StrictMock<mocks::AudioDriverMock>> driverMock =
        std::make_shared<StrictMock<mocks::AudioDriverMock>>();
    std::vector<std::unique_ptr<AudioTrackMock>> handles{};

};

TEST_CASE_METHOD(TestContext, "AudioStream valid flow", "[AudioPlaybackStream]") {
    auto stream = std::make_unique<AudioPlaybackStream<uint32_t>>(config, driverMock);

    SECTION("connect to the stream") {
        std::optional<TrackHandle> trackHandleOpt = generateTrackHandle();
        EXPECT_CALL(*driverMock, createAsyncTrack(ConfigMatcher(config), _))
            .WillOnce(Return(trackHandleOpt));

        stream->connect([] (auto&) { });
        REQUIRE(stream->getState() == StateType::Connected);

        SECTION("The stream is connected so we can start the stream") {
            EXPECT_CALL(*driverMock, start(TrackHandleMatcher(*trackHandleOpt)))
                .WillOnce(Return(true));

            stream->start();
            REQUIRE(stream->getState() == StateType::Running);

            SECTION("The stream has been started. Now we gonna pause it") {
                EXPECT_CALL(*driverMock, pause(TrackHandleMatcher(*trackHandleOpt)))
                    .WillOnce(Return(true));
                stream->pause();
                REQUIRE(stream->getState() == StateType::Connected);
                stream->pause();
                REQUIRE(stream->getState() == StateType::Connected);

                SECTION("The stream is paused. Trying to restart") {
                    EXPECT_CALL(*driverMock, start(TrackHandleMatcher(*trackHandleOpt)))
                        .WillOnce(Return(true));
                    stream->start();
                    REQUIRE(stream->getState() == StateType::Running);

                    SECTION("Disconnecting") {
                        EXPECT_CALL(*driverMock, releaseTrack(TrackHandleMatcher(*trackHandleOpt)));
                        stream->disconnect();
                        REQUIRE(stream->getState() == StateType::Idle);

                        SECTION("Trying to start when stream is in Idle state") {
                            stream->start();
                            REQUIRE(stream->getState() == StateType::Idle);
                        }
                    }

                    SECTION("The stream is running. Trying to reconnect in running state") {
                        REQUIRE(*stream == StateType::Running);
                        std::optional<TrackHandle> newTrackHandleOpt = generateTrackHandle();
                        EXPECT_CALL(*driverMock, stop(TrackHandleMatcher(*trackHandleOpt)))
                            .WillOnce(Return(true));
                        EXPECT_CALL(*driverMock, releaseTrack(TrackHandleMatcher(*trackHandleOpt)));
                        EXPECT_CALL(*driverMock, createAsyncTrack(ConfigMatcher(config), _))
                           .WillOnce(Return(newTrackHandleOpt));

                        stream->connect([] (auto&) { });
                        REQUIRE(*stream == StateType::Connected);

                        SECTION("The stream is in connected state. Trying to stop it") {
                            REQUIRE(*stream == StateType::Connected);

                            EXPECT_CALL(*driverMock, stop(TrackHandleMatcher(*newTrackHandleOpt)))
                                .Times(0);
                            EXPECT_CALL(*driverMock, stop(TrackHandleMatcher(*trackHandleOpt)))
                                .Times(0);
                            stream->stop();
                            REQUIRE(*stream == StateType::Connected);
                        }

                        SECTION("The stream is in connected state. Trying to start then stop it") {
                            EXPECT_CALL(*driverMock, start(TrackHandleMatcher(*newTrackHandleOpt)))
                                .WillOnce(Return(true));
                            stream->start();
                            REQUIRE(*stream == StateType::Running);

                            EXPECT_CALL(*driverMock, stop(TrackHandleMatcher(*newTrackHandleOpt)))
                                .WillOnce(Return(true));
                            EXPECT_CALL(*driverMock, stop(TrackHandleMatcher(*trackHandleOpt)))
                                .Times(0);
                            stream->stop();
                            REQUIRE(*stream == StateType::Connected);
                        }
                    }
                }
            }
        }
    }
}

} // namespace tests
} // namespace wasabi
