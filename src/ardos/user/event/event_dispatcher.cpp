#include "ardos/user/event.h"
#include <algorithm>

using namespace ardos::user::event;

EventDispatcher::EventDispatcher()
{
    listeners = new std::vector<EventListener*>();
}

void EventDispatcher::dispatch(const Event& event)
{
    for (auto* listener : *listeners)
    {
        listener->OnEvent(event);
    }
}

void EventDispatcher::registerListener(EventListener* listener)
{
    listeners->push_back(listener);
}

void EventDispatcher::unregisterListener(EventListener* listener)
{
    auto it = std::remove(listeners->begin(), listeners->end(), listener);
    if (it != listeners->end())
    {
        listeners->erase(it, listeners->end());
    }
}