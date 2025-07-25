#pragma once

#include <ardos/bus/message_bus.h>
#include <ardos/process/process_context.h>

using namespace ardos::bus;

namespace ardos::process
{
    class ManagedProcess : public MessageListener
    {
      public:
        virtual void start() = 0; // Start the application
        virtual void stop() = 0;  // Stop the application
        virtual void run() = 0;
        virtual ~ManagedProcess() = default; // Virtual destructor for cleanup
    };
} // namespace ardos::process