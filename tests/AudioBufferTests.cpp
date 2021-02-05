
#define CATCH_CONFIG_MAIN

#include "include/catch.hpp"

#include "AudioBuffer.hpp"


namespace wasabi {

using namespace audio::base;

namespace tests {

TEST_CASE("Initialization", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer{};
    REQUIRE(buffer.length() == 0);

    AudioBuffer<uint32_t> buffer2(20, 1);
    REQUIRE(buffer2.length() == 20);
}


TEST_CASE("putSample and getSample", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer(5, 1);
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
    AudioBuffer<uint32_t> buffer(10, 1);
    REQUIRE(buffer.length() == 10);
    REQUIRE(buffer.getPosition() == 0);
    REQUIRE(buffer.advance(5) == 5);
    REQUIRE(buffer.getPosition() == 5); 
}

TEST_CASE("iterators", "[AudioBuffer]") {
    // mutable buffer
    {
        AudioBuffer<uint32_t> buffer(100, 1);
        REQUIRE(buffer.length() == 100);

        uint32_t seed{};
        for (auto& sample : buffer) {
            sample = seed++;
        }

        seed = 0;
        for (auto itr = buffer.begin(); itr != buffer.end(); ++itr) {
            REQUIRE(*itr == seed++);
        }

        const auto i = buffer.getSample(10);
        REQUIRE(buffer.getSample(10) == 10);
        REQUIRE(buffer.getSample(55) == 55);
        REQUIRE(buffer.getSample(99) == 99);
    }

    // const buffer
    {
        const AudioBuffer<uint32_t> buffer(50, 1);
        for (auto itr = buffer.cbegin(); itr != buffer.cend(); ++itr) {
            REQUIRE(*itr == 0);
        }
    }
}

TEST_CASE("data", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer(10, 1);
    uint32_t* data = buffer.data();
    data[9] = 123;

    REQUIRE(buffer.getSample(9) == 123);
}

TEST_CASE("setPosition", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer(10, 1);
    REQUIRE_THROWS(buffer.setPosition(10));
}

TEST_CASE("operator[]", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer(10, 1);

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
// TODO: iterate channels from 0, not 1
TEST_CASE("operator[][]", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer(10, 1);

    uint32_t n = 0;
    for (uint32_t i = 0; i < buffer.length(); ++i) {
        buffer[i][1] = n;
        ++n;
    }

    n = 0;
    for (uint32_t i = 0; i < buffer.length(); ++i) {
        REQUIRE(buffer.getSample(i) == n);
        ++n;
    }
}

TEST_CASE("reallocate", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer(55, 1);
    REQUIRE(buffer.length() == 55);

    buffer.reallocate(30);
    REQUIRE(buffer.length() == 30);

    buffer.reallocate(100);
    REQUIRE(buffer.length() == 100);
}

} // namespace tests
} // namespace wasabi
