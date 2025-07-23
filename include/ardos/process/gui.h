#pragma once

#include "ardos/process/managed_process.h"

namespace ardos::process
{

    class Gui : public ManagedProcess
    {
      public:
        void start(ProcessContext* context) override;
        void stop() override;
        void run() override;
        void onMessage(const std::string& topic, const Message& message) override;
    };

} // namespace ardos::process