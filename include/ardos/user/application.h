#pragma once

#include <ardos/process/managed_process.h>
#include <ardos/user/event.h>

using namespace ardos::process;
using namespace ardos::bus;

namespace ardos::user
{
    class Application : public ManagedProcess
    {
      public:
        void onMessage(const std::string& topic, const Message& message) override;

      protected:
        event::EventDispatcher* getEventDispatcher() const;
        ;

      private:
        event::EventDispatcher* eventDispatcher = nullptr;
    };
} // namespace ardos::user
