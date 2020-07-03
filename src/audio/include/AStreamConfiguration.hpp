
#pragma once

#include "AudioTypes.hpp"

#include <string>


namespace wasabi {
namespace audio {

struct AStreamConfiguration
{
    std::string m_deviceName;
    base::SampleRate m_sampleRate;
    base::Channels m_channels;
    base::Volume m_volume;
    std::size_t m_bufferSize;
};


} // namespace audio
} // namespace wasabi