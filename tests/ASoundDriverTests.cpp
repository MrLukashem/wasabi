
#include "include/catch.hpp"

#include "ASoundAudioDriver.hpp"

#define ALSA_SUPPORTED 1


namespace wasabi {

using namespace audio::drivers;

namespace tests {

struct ASoundDriverTestContext {
    std::shared_ptr<AudioDriver> aSoundDriver = std::make_shared<ASoundAudioDriver>();
};

TEST_CASE_METHOD(ASoundDriverTestContext, "ASoundDriver basic flow", "[ASoundAudioDriver]") {
    AConfiguration config;
    audio::base::AudioBuffer<> buffer{};
    auto trackHandleOpt = aSoundDriver->createAsyncTrack(
        config, buffer, [] (auto) { return audio::base::AudioBuffer(); });
    REQUIRE(trackHandleOpt);
    REQUIRE(*trackHandleOpt != nullptr);

    SECTION("Starting created track") {
        REQUIRE(aSoundDriver->start(*trackHandleOpt));

        SECTION("Pausing running track") {
            REQUIRE(aSoundDriver->pause(*trackHandleOpt));

            SECTION("Resume paused track") {
                REQUIRE(aSoundDriver->start(*trackHandleOpt));
            }
            SECTION("stop paused track") {
                REQUIRE(aSoundDriver->stop(*trackHandleOpt));
            }
            SECTION("flush paused track") {
                REQUIRE(aSoundDriver->flush(*trackHandleOpt));
            }
        }
        SECTION("Stoppping running track") {
            REQUIRE(aSoundDriver->stop(*trackHandleOpt));

            SECTION("Restart stopped track") {
                REQUIRE(aSoundDriver->start(*trackHandleOpt));
            }
            SECTION("Pause stopped track") {
                REQUIRE_FALSE(aSoundDriver->pause(*trackHandleOpt));
            }
            SECTION("Flush stopped track") {
                REQUIRE_FALSE(aSoundDriver->flush(*trackHandleOpt));
            }
        }
        SECTION("Flushing running track") {
            REQUIRE_FALSE(aSoundDriver->flush(*trackHandleOpt));
        }
        SECTION("Starting running track") {
            REQUIRE_FALSE(aSoundDriver->start(*trackHandleOpt));
        }
    }

    SECTION("Stoping created track") {
        REQUIRE_FALSE(aSoundDriver->stop(*trackHandleOpt));
    }

    SECTION("Pausing created track") {
        REQUIRE_FALSE(aSoundDriver->pause(*trackHandleOpt));
    }

    SECTION("Flushing created track") {
        REQUIRE_FALSE(aSoundDriver->flush(*trackHandleOpt));
    }

    SECTION("Releasing created track") {
        aSoundDriver->releaseTrack(*trackHandleOpt);
    }
}

TEST_CASE_METHOD(ASoundDriverTestContext, "Releasing/creating track", "[ASoundAudioDriver]") {
    SECTION("Release empty track") {
        aSoundDriver->releaseTrack(nullptr);
    }
}

} // namespace tests
} // namespace tests
