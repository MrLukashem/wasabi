
#pragma once

#include <memory>


namespace wasabi {
namespace audio {

class AudioStream;

class StreamBuilder {
public:
    StreamBuilder() = default;
    ~StreamBuilder() = default;

    operator std::unique_ptr<AudioStream>() const;

    StreamBuilder& sampleRate();
    StreamBuilder& bitDepth();
    StreamBuilder& channels();
};

} // namespace audio
} // namespace wasabi
