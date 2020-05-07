
#pragma once

#include <memory>

#include "AudioTypes.hpp"
#include "Builder.hpp"

namespace wasabi {
namespace audio {

class AudioStream;

class StreamBuilder : public Builder<AudioStream> {
public:
    StreamBuilder() = default;
    virtual ~StreamBuilder() = default;

    operator std::unique_ptr<AudioStream>() const override;
    std::unique_ptr<AudioStream> build() const override;

    inline StreamBuilder& sampleRate(base::SampleRate sampleRate) {
        m_sampleRate = sampleRate;
    }

    inline StreamBuilder& bitDepth(base::BitDepth bitDepth) {
        m_bitDepth = bitDepth;
    }

    inline StreamBuilder& channels(base::Channels channels) {
        m_channels = channels;
    }
private:
    base::SampleRate m_sampleRate;
    base::BitDepth m_bitDepth;
    base::Channels m_channels;
};

} // namespace audio
} // namespace wasabi
