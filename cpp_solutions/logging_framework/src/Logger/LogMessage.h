#pragma once
#include "LogLevel.h"

namespace logger
{
    struct LogMessage
    {
        std::chrono::system_clock::time_point time_;
        LogLevel level_;
        std::string message_;

        friend std::ostream& operator<<(std::ostream& os, const LogMessage& message)
        {
            os << "timestamp=" << message.time_ << " level=" << to_string(message.level_).value_or("Unknown") << " message=" << message.message_;
            return os;
        }

    };
}
