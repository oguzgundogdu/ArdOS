#pragma once
#include "ardos/drivers/driver.h"

#define TIME_TICK_MESSAGE "time/tick"

namespace ardos::drivers
{

    class RTC : public Driver
    {
      public:
        void start() override;
        void stop() override;
        void run() override;
    };

} // namespace ardos::drivers