#include "ardos/kernel/process.h"
#include "ardos/user/application.h"
#include "ardos/user/event.h"
#include <ardos/gui/event.h>
#include <cstdint>

using namespace ardos::user::event;
using namespace ardos::gui::event;
using namespace ardos::kernel;
using namespace ardos::gui;
using namespace ardos::user;

ComponentEventListener::ComponentEventListener() : EventListener()
{
    Application* app = static_cast<Application*>(ProcessManager::getCurrentProcess()->getApplication());
    if (app != nullptr)
    {
        auto* eventDispatcher = app->getEventDispatcher();
        if (eventDispatcher != nullptr)
        {
            this->setListenerId(eventDispatcher->getNextEventSeq()); // Increment the ID for this listener
            eventDispatcher->registerListener(EventType::Touch, this);
            this->eventDispatcher = eventDispatcher; // Store the dispatcher for later use
        }
    }
}

void ComponentEventListener::OnEvent(Event& e)
{
    if (e.cancel || e.id < this->getListenerId())
        return;
    if (e.type == EventType::Touch)
    {
        if (std::find(e.elementIds->begin(), e.elementIds->end(), (uintptr_t)this) != e.elementIds->end())
        {
            onTouch(e);
        }
        else
        {
            onBlur(e); // Call onBlur if the event is not for this component
        }
    }
    else if (e.type == EventType::TimeChange)
    {
        onTimeTick(e);
    }
}

void ComponentEventListener::onTimeTick(Event& e)
{
    // Default implementation does nothing, can be overridden by derived classes
}