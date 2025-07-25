#pragma once

#include <cstdint>
#include <vector>

namespace ardos::user::event
{

    enum class EventType : std::uint8_t
    {
        Touch,
        RenderPanel,
        RenderContainer,
        RenderWindow,
        RenderButton,
        RenderMenuBar,
        RenderContextMenu,
    };

    struct Event
    {
        EventType type; // Exp: Touch
        int16_t x, y;
        uintptr_t id;         // Unique identifier for the event
        void* data = nullptr; // Additional data if needed
        uint32_t elementId;
    };

    class EventListener
    {
      public:
        virtual void OnEvent(const Event& e) = 0;
    };

    class EventDispatcher
    {
      private:
        std::vector<EventListener*>* listeners = nullptr;

      public:
        EventDispatcher();
        ~EventDispatcher();
        void dispatch(const Event& event);
        void registerListener(EventListener* listener);
        void unregisterListener(EventListener* listener);
    };
} // namespace ardos::user::event