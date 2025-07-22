#include "ardos/kernel/event_manager.h"

namespace ardos::kernel
{

    std::vector<EventListener*> EventManager::listeners;

    void EventManager::dispatch(const Event& event)
    {
        for (auto* listener : listeners)
        {
            listener->OnEvent(event);
        }
    }

    void EventManager::registerListener(EventListener* listener)
    {
        listeners.push_back(listener);
    }

    void EventManager::unregisterListener(EventListener* listener)
    {
        auto it = std::remove(listeners.begin(), listeners.end(), listener);
        if (it != listeners.end())
        {
            listeners.erase(it, listeners.end());
        }
    }

} // namespace ardos::kernel