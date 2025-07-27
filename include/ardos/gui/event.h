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
        virtual void onTouch(Event& e) = 0;
        virtual void onBlur(Event& e) = 0;
        virtual void onTimeTick(Event& e);
        EventDispatcher* getEventDispatcher() const
        {
            return eventDispatcher;
        }

      private:
        EventDispatcher* eventDispatcher = nullptr;
    };
} // namespace ardos::gui::event