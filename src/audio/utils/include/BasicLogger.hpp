
#pragma once

#include "spdlog/spdlog.h"


namespace wasabi::audio::utils {

class BasicLogger {
public:
    BasicLogger(const std::string& name) {
        setup(name);
    }
    ~BasicLogger() = default;
    // No one inhertis from the class therfore virtual destructor is reduntant

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
