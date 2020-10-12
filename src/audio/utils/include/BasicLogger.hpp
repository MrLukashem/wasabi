
#pragma once


#include <type_traits>

#include "spdlog/spdlog.h"

// TOOD: complete implementation of ths logger
namespace wasabi::audio::utils {

class BasicLogger {
public:
    BasicLogger(const std::string& name) {
        setup(name);
    }

    template <typename T>
    void trace(const T& msg) {
        m_logger->trace(msg);
    }

    template <typename T>
    void debug(const T& msg) {
        m_logger->debug(msg);
    }

    template <typename T>
    void info(const T& msg) {
        m_logger->info(msg);
    }

    template <typename T>
    void warn(const T&msg) {
        m_logger->warn(msg);
    }

    template <typename T>
    void error(const T& msg) {
        m_logger->error(msg);
    }

    template <typename T>
    void critical(const T& msg) {
        m_logger->critical(msg);
    }

    template <
        typename T,
        typename std::enable_if<std::negation_v<std::is_void<T>>>::type* = nullptr>
    const void* toVoidPointer(T arg) {
        return static_cast<const void*>(arg);
    }

    template<
        typename FormatString,
        typename T,
        typename std::enable_if<std::is_pointer_v<T>>::type* = nullptr>
    void warn(const FormatString &fmt, const T& arg)
    {
        m_logger->warn(fmt, toVoidPointer(arg));
    }

    template<typename FormatString, typename... Args>
    void warn(const FormatString &fmt, Args... args)
    {
        m_logger->warn(fmt, args...);
    }
protected:
    void setup(const std::string& name) {
        using namespace spdlog;

        auto consoleSink = std::make_shared<sinks::ansicolor_stdout_sink_mt>();
        consoleSink->set_level(level::warn);

        m_logger = std::make_unique<logger>(name, consoleSink);
    }
private:
    std::unique_ptr<spdlog::logger> m_logger;
};

} // namespace wasabi::audio::utils
