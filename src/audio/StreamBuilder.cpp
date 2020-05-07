
#include "StreamBuilder.hpp"

#include "AudioStream.hpp"


namespace wasabi {
namespace audio {

StreamBuilder::operator std::unique_ptr<AudioStream>() const {
    return std::make_unique<AudioStream>();
}

std::unique_ptr<AudioStream> StreamBuilder::build() const {
    return std::make_unique<AudioStream>();
}

} // namespace audio
} // namespace wasabi
