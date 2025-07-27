#pragma once

#include "api/Common.h"
#include <cstdint>
#include <map>
#include <vector>

namespace ardos::user::event
{

    enum class EventType : std::uint8_t
    {
        Touch,
        Blur,
        TimeChange,
        RenderPanel,
        RenderContainer,
        RenderWindow,
        RenderButton,
        RenderMenuBar,
        RenderContextMenu,
        RenderLabel,
    };

    struct Event
    {
        EventType type; // Exp: Touch
        int16_t x, y;
        uint32_t id;                                        // Unique identifier for the event
        void* data = nullptr;                               // Additional data if needed
        const std::vector<uintptr_t>* elementIds = nullptr; // List of element IDs involved in the event
        bool cancel = false;                                // Flag to cancel the event
    };

    class EventListener
    {
      public:
        virtual void OnEvent(Event& e) = 0;
        uint32_t getListenerId() const
        {
            return mlistenerId;
        }
        void setListenerId(uint32_t id)
        {
            this->mlistenerId = id;
        }

      private:
        uint32_t mlistenerId;
    };

    class EventDispatcher
    {
      private:
        std::map<EventType, std::vector<EventListener*>>* listeners = nullptr;
        uint32_t mEventSeq = 0;

      public:
        EventDispatcher();
        ~EventDispatcher();
        void dispatch(Event& event);
        void registerListener(EventType, EventListener* listener);
        void unregisterListener(EventListener* listener);
        uint32_t getEventSeq() const;
        uint32_t getNextEventSeq();
    };
} // namespace ardos::user::event