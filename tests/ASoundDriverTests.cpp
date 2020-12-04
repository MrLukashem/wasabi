
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

    SECTION("Starting the track") {
        REQUIRE(aSoundDriver->start(*trackHandleOpt));

        SECTION("Pausing the track") {
            REQUIRE(aSoundDriver->pause(*trackHandleOpt));
        }
    }
}

} // namespace tests

} // namespace tests
