#pragma once

#include <ardos/user/event.h>

using namespace ardos::user::event;

namespace ardos::gui::event
{
    class ComponentEventListener : public EventListener
    {
      public:
        ComponentEventListener();
        void OnEvent(Event& e) override;

      protected:
        virtual void onTouch(void* data = nullptr) = 0;
        virtual void onBlur(void* data = nullptr) = 0;
        EventDispatcher* getEventDispatcher() const
        {
            return eventDispatcher;
        }

      private:
        EventDispatcher* eventDispatcher = nullptr;
    };
} // namespace ardos::gui::event