#pragma once

#include <functional>
#include <string>

namespace ardos::kernel
{

    enum class LogLevel
    {
        Info,
        Warning,
        Error,
        Debug
    };

    class Logger
    {
      public:
        static void Log(LogLevel level, const std::string& message);

        static void SetOutputHandler(std::function<void(LogLevel, const std::string&)> handler);

      private:
        static std::function<void(LogLevel, const std::string&)> outputHandler;
    };

} // namespace ardos::kernel