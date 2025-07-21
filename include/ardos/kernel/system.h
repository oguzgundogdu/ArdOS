#pragma once
#include <RTClib.h>
#include <ardos/gui/screen_manager.h>

namespace ardos::kernel
{

    class System
    {
      public:
        static void Start();
        static void Poll();

      private:
        static bool is_initialized;
        static ScreenManager* screenManager;
    };

} // namespace ardos::kernel