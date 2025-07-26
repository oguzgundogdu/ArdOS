#pragma once

#include <cstdint>
#include <vector>

namespace ardos::user::event
{

    enum class EventType : std::uint8_t
    {
        Touch,
        Blur,
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
        uintptr_t id;                                       // Unique identifier for the event
        void* data = nullptr;                               // Additional data if needed
        const std::vector<uintptr_t>* elementIds = nullptr; // List of element IDs involved in the event
        bool cancel = false;                                // Flag to cancel the event
    };

    class EventListener
    {
      public:
        virtual void OnEvent(Event& e) = 0;
    };

    class EventDispatcher
    {
      private:
        std::vector<EventListener*>* listeners = nullptr;

      public:
        EventDispatcher();
        ~EventDispatcher();
        void dispatch(Event& event);
        void registerListener(EventListener* listener);
        void unregisterListener(EventListener* listener);
    };
} // namespace ardos::user::event