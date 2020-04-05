
#define CATCH_CONFIG_MAIN

#include "include/catch.hpp"

#include "AudioBuffer.hpp"


TEST_CASE("Initialization", "[AudioBuffer]") {
    AudioBuffer<uint32_t> buffer{};
    REQUIRE(buffer.length() == 0);
}

TEST_CASE("Advance", "[AudioBuffer]") {
    AudioBuffer<uint32_t, 1> buffer(10);
    REQUIRE(buffer.position() == 0);
    REQUIRE(buffer.advance(5) == 5);
    REQUIRE(buffer.position() == 5); 
}
