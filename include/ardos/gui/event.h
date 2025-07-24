#pragma once

#include <ardos/user/event.h>

using namespace ardos::user::event;

namespace ardos::gui::event
{
    class ComponentEventListener : public EventListener
    {
      public:
        void OnEvent(const Event& e) override;

      protected:
        virtual void onTouch(void* data = nullptr) = 0;
    };
} // namespace ardos::gui::event