
#include "include/catch.hpp"

#include "TypeWrapper.hpp"


namespace wasabi {

using namespace audio::base;

namespace tests {

TEST_CASE("Init", "[TypeWrapper]") {
    using ChannelCount = TypeWrapper<uint8_t, struct ChannelCountTag>;
    ChannelCount channelCount{10};
}

TEST_CASE("operators", "[TypeWrapper]") {
    using ChannelCount = TypeWrapper<uint8_t, struct ChannelCountTag>;
    ChannelCount channelCount{10};
    REQUIRE(channelCount == 10);

    channelCount += 5;
    REQUIRE(channelCount == 15);

    channelCount -= 15;
    REQUIRE(channelCount == 0);

    channelCount = 3;
    ChannelCount channelCount2 = 2;
    auto result = channelCount - channelCount2;
    REQUIRE(result == 1);
    REQUIRE(channelCount == 3);
    REQUIRE(channelCount2 == 2);
}

} // namespace tests
} // namespace wasabi
