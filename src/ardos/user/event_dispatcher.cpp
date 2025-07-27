
#include "ardos/user/event.h"
#include <algorithm>
#include <cstdint>

using namespace ardos::user::event;

EventDispatcher::EventDispatcher()
{
    listeners = new std::map<EventType, std::vector<EventListener*>>();
}

void EventDispatcher::dispatch(Event& event)
{
    if (listeners->empty())
    {
        return;
    }

    for (const auto& [eventType, listenerList] : *listeners)
    {
        if (event.type != eventType)
        {
            continue;
        }

        if (listenerList.empty())
        {
            continue;
        }

        for (auto* listener : listenerList)
        {
            listener->OnEvent(event);
        }
    }
}

void EventDispatcher::registerListener(EventType eventType, EventListener* listener)
{
    if (listeners->find(eventType) == listeners->end())
    {
        (*listeners)[eventType] = std::vector<EventListener*>();
    }
    (*listeners)[eventType].push_back(listener);
}

void EventDispatcher::unregisterListener(EventListener* listener)
{
    for (auto& [eventType, listenerList] : *listeners)
    {
        auto it = std::remove(listenerList.begin(), listenerList.end(), listener);
        if (it != listenerList.end())
        {
            listenerList.erase(it, listenerList.end());
            break; // Listener found and removed, exit loop
        }
    }
}

uint32_t EventDispatcher::getEventSeq() const
{
    return mEventSeq;
}

uint32_t EventDispatcher::getNextEventSeq()
{
    return ++mEventSeq;
}