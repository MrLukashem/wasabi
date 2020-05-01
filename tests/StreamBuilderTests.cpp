
#include "include/catch.hpp"

#include "StreamBuilder.hpp"


namespace wasabi {

using namespace audio;

namespace tests {

TEST_CASE("[StreamBulder]", "Init") {
    StreamBuilder builder{};
}

} // nemspace tests
} // namespace wasabi