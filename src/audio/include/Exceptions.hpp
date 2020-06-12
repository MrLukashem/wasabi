
#pragma once

#include <stdexcept>


namespace wasabi {
namespace audio {
namespace base {

struct StateException : std::runtime_error
{
    StateException(const std::string& what) : std::runtime_error(what) {}
    virtual ~StateException() = default;
};

} // namespace base
} // namespace audio
} // namespace wasabi