#pragma once
#include <expected>
namespace logger
{
    enum class LogLevel {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        FATAL = 4
    };

    constexpr std::expected<std::string, std::string>to_string(LogLevel level) {
        using enum LogLevel;

        const std::array<std::string, 5> levels{
            "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"
        };

        const auto index = static_cast<std::size_t>(level);
        if (index >= levels.size()) {
            return std::unexpected( "Invalid Level provided");
        }
        return levels[index];
    }
}