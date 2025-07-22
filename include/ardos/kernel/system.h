#pragma once

#include <ardos/kernel/rtc.h>

namespace ardos::kernel
{

    class System
    {
      public:
        static void Start();
        static void Poll();

      private:
        static bool is_initialized;
    };

} // namespace ardos::kernel