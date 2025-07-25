#pragma once
#include "ardos/drivers/driver.h"
#include <string>

namespace ardos::drivers
{

    class SerialDriver : public Driver
    {
      public:
        void start() override;
        void stop() override;
        void run() override;
        static void Write(const std::string& msg);
    };

} // namespace ardos::drivers