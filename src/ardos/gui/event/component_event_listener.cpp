#include "ardos/kernel/process.h"
#include "ardos/user/application.h"
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
            eventDispatcher->registerListener(this);
            this->eventDispatcher = eventDispatcher; // Store the dispatcher for later use
        }
    }
}

void ComponentEventListener::OnEvent(Event& e)
{
    if (e.cancel)
        return;
    if (e.type == EventType::Touch)
    {
        if (std::find(e.elementIds->begin(), e.elementIds->end(), (uintptr_t)this) != e.elementIds->end())
        {
            onTouch(e.data);
            e.cancel = true; // Cancel the event to prevent further propagation
        }
        else
        {
            onBlur(e.data); // Call onBlur if the event is not for this component
        }
    }
    else
    {
        // Handle other event types if necessary
    }
}