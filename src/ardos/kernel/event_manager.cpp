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

} // namespace ardos::kernel