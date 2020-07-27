
#pragma once

#include <string>
#include <string_view>


namespace wasabi {
namespace audio {

class AudioDevice {
public:
    AudioDevice(const std::string& name);
    virtual ~AudioDevice() = default;

    virtual std::string_view name();
private:
    std::string m_name;
};

} // namespace audio
} // namespace wasabi