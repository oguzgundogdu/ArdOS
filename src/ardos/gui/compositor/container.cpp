#include "ardos/bus/message_bus.h"
#include "ardos/kernel/bus/fill_rect_message.h"
#include <ardos/gui/compositor.h>

using namespace ardos::gui;
using namespace ardos::bus;
using namespace ardos::kernel::bus;

void Compositor::renderContainer(Container* container, uint32_t pid)
{
    if (container)
    {
        MessageBus::publish(FILL_RECT_MESSAGE,
                            FillRectMessage(container->getX(), container->getY(), container->getWidth(),
                                            container->getHeight(), 0xFFFFFF, pid, MessageType::Display));
    }
}
