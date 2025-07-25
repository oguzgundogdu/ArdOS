#include "ardos/kernel/process.h"
#include "ardos/user/application.h"
#include <ardos/gui/event.h>

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
            eventDispatcher = eventDispatcher; // Store the dispatcher for later use
        }
    }
}

void ComponentEventListener::OnEvent(const Event& e)
{
    if (e.type == EventType::Touch)
    {
        onTouch(e.data);
    }
    else
    {
        // Handle other event types if necessary
    }
}