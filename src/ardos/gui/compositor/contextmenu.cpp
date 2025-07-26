#include "ardos/gui/compositor.h"
#include "ardos/kernel/bus/draw_rect_message.h"
#include "ardos/kernel/bus/fill_rect_message.h"
#include "ardos/kernel/bus/set_text_size_message.h"
#include <ardos/bus/message_bus.h>

using namespace ardos::bus;
using namespace ardos::kernel::bus;

void Compositor::renderContextMenu(ContextMenu* contextMenu, uint32_t pid)
{
    if (contextMenu->isVisible())
    {
        MessageBus::publish(FILL_RECT_MESSAGE,
                            FillRectMessage(contextMenu->getX(), contextMenu->getY(), contextMenu->getWidth(),
                                            contextMenu->getHeight(), contextMenu->getBackgroundColor(), pid,
                                            MessageType::Display));

        MessageBus::publish(DRAW_RECT_MESSAGE,
                            DrawRectMessage(contextMenu->getX(), contextMenu->getY(), contextMenu->getWidth(),
                                            contextMenu->getHeight(), contextMenu->getBackgroundColor(), pid,
                                            MessageType::Display));

        MessageBus::publish(SET_TEXT_SIZE_MESSAGE, SetTextSizeMessage(1, pid, MessageType::Display));
    }
    else
    {
        MessageBus::publish(FILL_RECT_MESSAGE,
                            FillRectMessage(contextMenu->getX(), contextMenu->getY(), contextMenu->getWidth(),
                                            contextMenu->getHeight(), 0x0000, pid, MessageType::Display));
    }
}
