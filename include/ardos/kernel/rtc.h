#pragma once
#include <RTClib.h>

namespace ardos::kernel
{

    class RTC
    {
      public:
        static void Start();
        static DateTime Now();
        static void Tick();

      private:
        static RTC_DS3231* rtc;
        static DateTime last_known;
    };

} // namespace ardos::kernel