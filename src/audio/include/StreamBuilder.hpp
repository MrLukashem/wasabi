
#pragma once

#include <memory>

#include "AudioPlaybackStream.hpp"
#include "AudioTypes.hpp"
#include "Builder.hpp"

namespace wasabi {
namespace audio {

template <typename SampleType>
class StreamBuilder : public Builder<AudioStream<SampleType>> {
public:
    StreamBuilder() = default;
    virtual ~StreamBuilder() = default;

    // TODO: checks to check if AudioStream is able to be created from set data
    operator std::unique_ptr<AudioStream<SampleType>>() const {
        return std::make_unique<AudioPlaybackStream<SampleType>>();
    }

    std::unique_ptr<AudioStream<SampleType>> build() const {
        return std::make_unique<AudioPlaybackStream<SampleType>>();
    }

    inline StreamBuilder& device(const std::string& name) {
        m_deviceName = name;
        return *this;
    }

    inline StreamBuilder& sampleRate(base::SampleRate sampleRate) {
        m_sampleRate = sampleRate;
        return *this;
    }

    inline StreamBuilder& channels(base::Channels channels) {
        m_channels = channels;
        return *this;
    }

    inline StreamBuilder& volume(base::Volume volume) {
        m_volume = volume;
        return *this;
    }
private:
    std::string m_deviceName;
    base::SampleRate m_sampleRate;
    base::Channels m_channels;
    base::Volume m_volume;
};

} // namespace audio
} // namespace wasabi
