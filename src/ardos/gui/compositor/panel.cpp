#include "ardos/kernel/bus/draw_rect_message.h"
#include <ardos/bus/message_bus.h>
#include <ardos/gui/compositor.h>
#include <ardos/gui/panel.h>
#include <ardos/kernel/bus/fill_rect_message.h>
#include <cstdint>

using namespace ardos::bus;
using namespace ardos::kernel::bus;

void Compositor::addPanel(Panel* panel, uint32_t pid)
{
    if (panel == nullptr)
    {
        return;
    }

    renderPanel(panel, pid);
}

void Compositor::renderPanel(Panel* panel, uint32_t pid)
{
    if (panel == nullptr)
    {
        return;
    }

    if (panel->isVisible())
    {
        MessageBus::publish(FILL_RECT_MESSAGE,
                            FillRectMessage(panel->getX(), panel->getY(), panel->getWidth(), panel->getHeight(),
                                            panel->getBackgroundColor(), pid, MessageType::Display));

        MessageBus::publish(DRAW_RECT_MESSAGE,
                            DrawRectMessage(panel->getX(), panel->getY(), panel->getWidth(), panel->getHeight(),
                                            panel->getBorderColor(), pid, MessageType::Display));
    }
    else
    {
        MessageBus::publish(FILL_RECT_MESSAGE, FillRectMessage(panel->getX(), panel->getY(), panel->getWidth(),
                                                               panel->getHeight(), 0x0, pid, MessageType::Display));
    }
}

Panel* Compositor::getPanelById(uintptr_t id)
{

    return nullptr;
}