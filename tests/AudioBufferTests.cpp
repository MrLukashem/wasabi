
#define CATCH_CONFIG_MAIN

#include "include/catch.hpp"

#include "AudioBuffer.hpp"


namespace wasabi {

using namespace audio::base;

namespace tests {

TEST_CASE("Initialization", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer{};
    REQUIRE(buffer.length() == 0);

    AudioBuffer<uint32_t> buffer2(20);
    REQUIRE(buffer2.length() == 20);
}


TEST_CASE("putSample and getSample", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer(5);
    REQUIRE(buffer.length() == 5);

    buffer.putSample(1);
    buffer.putSample(2);
    buffer.putSample(3);
    buffer.putSample(5);
    buffer.putSample(7);
    REQUIRE(buffer.length() == 5);

    buffer.setPosition(0);
    REQUIRE(buffer.getNextSample() == 1);
    REQUIRE(buffer.getNextSample() == 2);
    REQUIRE(buffer.getNextSample() == 3);
    REQUIRE(buffer.getNextSample() == 5);
    REQUIRE(buffer.getNextSample() == 7);
    REQUIRE(buffer.length() == 5);
}

TEST_CASE("advance", "[AudioBuffer]") {
    AudioBuffer<uint32_t, 1> buffer(10);
    REQUIRE(buffer.length() == 10);
    REQUIRE(buffer.position() == 0);
    REQUIRE(buffer.advance(5) == 5);
    REQUIRE(buffer.position() == 5); 
}

TEST_CASE("iterators", "[AudioBuffer]") {
    AudioBuffer<uint32_t, 1> buffer(100);
    REQUIRE(buffer.length() == 100);

    uint32_t seed{};
    const auto& generateSample = [&seed] () {
        return seed++;
    };

    for (auto& sample : buffer) {
        sample = generateSample();
    }

    seed = 0;
    for (auto itr = buffer.begin(); itr != buffer.end(); ++itr) {
        REQUIRE(*itr == generateSample());
    }

    REQUIRE(buffer.getSample(10) == 10);
    REQUIRE(buffer.getSample(55) == 55);
    REQUIRE(buffer.getSample(99) == 99);
}

TEST_CASE("data", "[AudioBuffer]") {
    AudioBuffer<uint32_t, 1> buffer(10);
    uint32_t* data = buffer.data();
    data[9] = 123;

    REQUIRE(buffer.getSample(9) == 123);
}

TEST_CASE("setPosition", "[AudioBuffer]") {
    AudioBuffer<uint32_t, 1> buffer(10);
    REQUIRE_THROWS(buffer.setPosition(10));
}

TEST_CASE("operator[]", "[AudioBuffer]") {
    AudioBuffer<uint32_t, 1> buffer(10);

    uint32_t n = 0;
    for (uint32_t i = 0; i < buffer.length(); ++i) {
        buffer[i] = n;
        ++n;
    }

    n = 0;
    for (uint32_t i = 0; i < buffer.length(); ++i) {
        REQUIRE(buffer.getSample(i) == n);
        ++n;
    }
}

// TODO: make test for more channels
TEST_CASE("operator[][]", "[AudioBuffer]") {
    AudioBuffer<uint32_t, 1> buffer(10);

    uint32_t n = 0;
    for (uint32_t i = 0; i < buffer.length(); ++i) {
        buffer[i][0] = n;
        ++n;
    }

    n = 0;
    for (uint32_t i = 0; i < buffer.length(); ++i) {
        REQUIRE(buffer.getSample(i) == n);
        ++n;
    }
}

} // namespace tests
} // namespace wasabi
