#include "Arduino.h"
#include "api/Common.h"
#include "ardos/gui/panel.h"
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
            this->setListenerId(eventDispatcher->getNextEventSeq()); // Increment the ID for this listener
            eventDispatcher->registerListener(this);
            this->eventDispatcher = eventDispatcher; // Store the dispatcher for later use
        }
    }
}

void ComponentEventListener::OnEvent(Event& e)
{
    Serial.println("Event id: " + String(e.id) + ", Listener id: " + String(this->getListenerId()));
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
    else
    {
        // Handle other event types if necessary
    }
}