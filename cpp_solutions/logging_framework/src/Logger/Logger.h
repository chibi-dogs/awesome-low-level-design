#pragma once
#include <chrono>
#include <memory>
#include "ILogSink.h"
#include <filesystem>

namespace logger {
    struct LoggerConfig
    {
        LogLevel m_LogLevel = LogLevel::INFO;
        bool m_LogToConsole = true;
        std::filesystem::path pathToLogFile {};
    };

    class Logger {
    public:
        explicit Logger(const LoggerConfig& config);

        static void debug();
        static void info();
        static void warn();
        static void error();
        static void fatal();

    private:
        LoggerConfig m_Config;
    };
}