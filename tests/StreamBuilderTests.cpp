
#include "include/catch.hpp"

#include "AudioStream.hpp"
#include "StreamBuilder.hpp"


namespace wasabi {

using namespace audio;

namespace tests {

TEST_CASE("[StreamBulder]", "Init") {
    StreamBuilder<uint32_t> builder{};
}

TEST_CASE("[StreamBuilder]", "Creating a AudioStream") {
    StreamBuilder<uint32_t> builder{};
    auto firstStream = builder
        .channels(1)
        .sampleRate(48).build();

    builder.sampleRate(24);
    builder.volume(0.5f);
    auto secondStream = builder;
}

} // nemspace tests
} // namespace wasabi