#include "ardos/kernel/logger.h"
#include <iostream>

namespace ardos::kernel
{

    std::function<void(LogLevel, const std::string&)> Logger::outputHandler = nullptr;

    void Logger::Log(LogLevel level, const std::string& message)
    {
        if (outputHandler)
        {
            outputHandler(level, message);
        }
        else
        {
            const char* levelStr = "";
            switch (level)
            {
            case LogLevel::Info:
                levelStr = "[INFO]";
                break;
            case LogLevel::Warning:
                levelStr = "[WARN]";
                break;
            case LogLevel::Error:
                levelStr = "[ERROR]";
                break;
            case LogLevel::Debug:
                levelStr = "[DEBUG]";
                break;
            }

            std::cout << levelStr << " " << message << std::endl;
        }
    }

    void Logger::SetOutputHandler(std::function<void(LogLevel, const std::string&)> handler)
    {
        outputHandler = std::move(handler);
    }

} // namespace ardos::kernel