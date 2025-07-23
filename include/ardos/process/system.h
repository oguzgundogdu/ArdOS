#pragma once

#include "ardos/process/managed_process.h"

namespace ardos::process
{

    class System : public ManagedProcess
    {
      public:
        void start(ProcessContext* context) override;
        void stop() override;
        void run() override;
    };

} // namespace ardos::process