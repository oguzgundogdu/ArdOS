#include "ardos/bus/message_bus.h"
#include "ardos/kernel/process.h"
#include <ardos/bus/touch_message.h>
#include <ardos/gui/bus/render_component_message.h>
#include <ardos/user/application.h>

using namespace ardos::user;

void Application::onMessage(const std::string& topic, const Message& message)
{
    auto* context = kernel::ProcessManager::getCurrentProcess()->getContext();
    if (context->getPid() != message.getSourcePid())
    {
        return; // Ignore messages not from this process
    }
    if (message.getType() == MessageType::Input)
    {
        const TouchMessage& inputMessage = static_cast<const TouchMessage&>(message);

        Event event;
        event.type = EventType::Touch;
        event.x = inputMessage.getX();
        event.y = inputMessage.getY();
        event.id = inputMessage.getSourcePid();
        event.elementId = inputMessage.getElementId();

        getEventDispatcher()->dispatch(event);
    }
}

void Application::OnEvent(const Event& e)
{
    auto* context = kernel::ProcessManager::getCurrentProcess()->getContext();
    switch (e.type)
    {
    case EventType::RenderPanel:
        MessageBus::publish(RENDER_PANEL_MESSAGE, gui::bus::RenderComponentMessage(e.elementId, context->getPid()));
        break;
    case EventType::RenderContainer:
        MessageBus::publish(RENDER_CONTAINER_MESSAGE, gui::bus::RenderComponentMessage(e.elementId, context->getPid()));
        break;
    case EventType::RenderWindow:
        MessageBus::publish(RENDER_WINDOW_MESSAGE, gui::bus::RenderComponentMessage(e.elementId, context->getPid()));
        break;
    case EventType::RenderButton:
        MessageBus::publish(RENDER_BUTTON_MESSAGE, gui::bus::RenderComponentMessage(e.elementId, context->getPid()));
        break;
    case EventType::RenderMenuBar:
        MessageBus::publish(RENDER_MENUBAR_MESSAGE, gui::bus::RenderComponentMessage(e.elementId, context->getPid()));
        break;
    case EventType::RenderContextMenu:
        MessageBus::publish(RENDER_CONTEXTMENU_MESSAGE,
                            gui::bus::RenderComponentMessage(e.elementId, context->getPid()));
        break;
    default:
        break;
    }
}