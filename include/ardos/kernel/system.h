#pragma once

#include "ardos/kernel/process.h"
#include <ardos/kernel/rtc.h>

namespace ardos::kernel
{

    class System : public Application
    {
      public:
        void start(ardos::kernel::ProcessContext* context) override;
        void stop() override;
        void run() override;

        static System* getInstance()
        {
            if (!instance)
            {
                instance = new System();
            }
            return instance;
        }

      private:
        bool is_initialized;
        static System* instance;
    };

} // namespace ardos::kernel