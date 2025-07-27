#include "ardos/bus/message_bus.h"
#include "ardos/kernel/logger.h"
#include "ardos/kernel/process.h"
#include "ardos/user/event.h"
#include <ardos/bus/touch_message.h>
#include <ardos/gui/bus/render_component_message.h>
#include <ardos/user/application.h>

using namespace ardos::user;

Application::Application() : ManagedProcess()
{
    // Initialize the event dispatcher
    eventDispatcher = new event::EventDispatcher();
    // Register this application as an event listener
    eventDispatcher->registerListener(EventType::RenderButton, this);
    eventDispatcher->registerListener(EventType::RenderContainer, this);
    eventDispatcher->registerListener(EventType::RenderLabel, this);
    eventDispatcher->registerListener(EventType::RenderMenuBar, this);
    eventDispatcher->registerListener(EventType::RenderContextMenu, this);
    eventDispatcher->registerListener(EventType::RenderPanel, this);
    eventDispatcher->registerListener(EventType::RenderWindow, this);

    MessageBus::subscribe(TOUCH_START_MESSAGE, this);
    MessageBus::subscribe(TOUCH_MOVE_MESSAGE, this);
    MessageBus::subscribe(TOUCH_END_MESSAGE, this);
}

void Application::onMessage(const std::string& topic, const Message& message)
{
    auto* context = kernel::ProcessManager::getCurrentProcess()->getContext();
    if (context->getPid() != message.getSourcePid())
    {
        return; // Ignore messages not from this process
    }
    if (message.getType() == MessageType::Input)
    {
        kernel::Logger::Log(kernel::LogLevel::Debug, "Application received input message: " + topic);
        const TouchMessage& inputMessage = static_cast<const TouchMessage&>(message);

        Event event;

        event.type = EventType::Touch;
        event.x = inputMessage.getX();
        event.y = inputMessage.getY();
        event.id = this->eventDispatcher->getEventSeq();
        event.elementIds = inputMessage.getElementIds();

        getEventDispatcher()->dispatch(event);
    }
}

void Application::OnEvent(Event& e)
{
    auto* context = kernel::ProcessManager::getCurrentProcess()->getContext();
    switch (e.type)
    {
    case EventType::RenderPanel:
        MessageBus::publish(RENDER_PANEL_MESSAGE, gui::bus::RenderComponentMessage(e.data, context->getPid()));
        break;
    case EventType::RenderContainer:
        MessageBus::publish(RENDER_CONTAINER_MESSAGE, gui::bus::RenderComponentMessage(e.data, context->getPid()));
        break;
    case EventType::RenderWindow:
        MessageBus::publish(RENDER_WINDOW_MESSAGE, gui::bus::RenderComponentMessage(e.data, context->getPid()));
        break;
    case EventType::RenderButton:
        MessageBus::publish(RENDER_BUTTON_MESSAGE, gui::bus::RenderComponentMessage(e.data, context->getPid()));
        break;
    case EventType::RenderMenuBar:
        MessageBus::publish(RENDER_MENUBAR_MESSAGE, gui::bus::RenderComponentMessage(e.data, context->getPid()));
        break;
    case EventType::RenderContextMenu:
        MessageBus::publish(RENDER_CONTEXTMENU_MESSAGE, gui::bus::RenderComponentMessage(e.data, context->getPid()));
        break;
    case EventType::RenderLabel:
        MessageBus::publish(RENDER_LABEL_MESSAGE, gui::bus::RenderComponentMessage(e.data, context->getPid()));
        break;
    default:
        break;
    }
}

event::EventDispatcher* Application::getEventDispatcher() const
{
    return eventDispatcher;
}