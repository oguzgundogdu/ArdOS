#pragma once
#include "ardos/drivers/serial.h"
#include "ardos/kernel/logger.h"

namespace ardos::platform
{

    class SerialLogHandler
    {
      public:
        static void Init()
        {
            using namespace ardos::kernel;
            using namespace ardos::drivers;

            Logger::SetOutputHandler(
                [](LogLevel level, const std::string& msg)
                {
                    std::string fullMessage;
                    switch (level)
                    {
                    case LogLevel::Info:
                        fullMessage = "[INFO] ";
                        break;
                    case LogLevel::Warning:
                        fullMessage = "[WARN] ";
                        break;
                    case LogLevel::Error:
                        fullMessage = "[ERROR] ";
                        break;
                    case LogLevel::Debug:
                        fullMessage = "[DEBUG] ";
                        break;
                    }
                    fullMessage += msg;
                    SerialDriver::Write(fullMessage);
                });
        }
    };

} // namespace ardos::platform