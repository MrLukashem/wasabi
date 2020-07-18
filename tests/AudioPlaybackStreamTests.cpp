
#include "include/catch.hpp"

#include "AudioPlaybackStream.hpp"
#include "AudioDriverMock.hpp"


namespace wasabi {

using namespace audio::base;
using audio::AudioPlaybackStream;

namespace tests {

std::unique_ptr<audio::drivers::AudioDriver> driverMock =
    std::make_unique<mocks::AudioDriverMock>();

TEST_CASE("Init", "[AudioPlaybackStream]") {
    auto stream = std::make_unique<AudioPlaybackStream<uint32_t>>();
}

} // namespace tests
} // namespace wasabi