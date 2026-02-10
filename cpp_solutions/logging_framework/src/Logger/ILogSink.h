#pragma once

#include "LogMessage.h"
#include <iostream>
namespace logger
{
    class ILogSink {

    public:
        virtual ~ILogSink() = default;
        virtual void Log(const LogMessage& message) = 0;

    };

    class ConsoleLogSink final : public ILogSink
    {
        public:
        ConsoleLogSink();
        void Log(const LogMessage& message) override
        {
            std::cout << message << std::endl;
        }
    };

    class FileLogSink final : public ILogSink
    {
        public:
        FileLogSink();
        void Log(const LogMessage& message) override;
    };
}