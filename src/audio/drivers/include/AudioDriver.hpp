
#pragma once

#include "AConfiguration.hpp"


namespace wasabi {
namespace audio {
namespace drivers {

class AudioDriver {
public:
    AudioDriver(const AConfiguration& config): m_config{config} {}

    virtual ~AudioDriver() = default;

    virtual bool setNewAConfiguration(const AConfiguration& config);
protected:
    AConfiguration m_config;
};

} // namespace drivers
} // namespace audio
} // namespace wasabi

