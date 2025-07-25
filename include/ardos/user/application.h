#pragma once

#include <ardos/process/managed_process.h>
#include <ardos/user/event.h>

using namespace ardos::process;
using namespace ardos::bus;
using namespace ardos::user::event;

namespace ardos::user
{
    class Application : public ManagedProcess, public EventListener
    {
      public:
        Application();
        void onMessage(const std::string& topic, const Message& message) override;
        void OnEvent(const Event& e) override;
        event::EventDispatcher* getEventDispatcher() const;

      protected:
      private:
        event::EventDispatcher* eventDispatcher = nullptr;
    };
} // namespace ardos::user
