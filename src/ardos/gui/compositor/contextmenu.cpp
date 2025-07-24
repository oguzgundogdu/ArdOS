#include "ardos/gui/button.h"
#include "ardos/gui/compositor.h"
#include "ardos/kernel/bus/draw_rect_message.h"
#include "ardos/kernel/bus/fill_rect_message.h"
#include "ardos/kernel/bus/set_text_size_message.h"
#include <ardos/bus/message_bus.h>

using namespace ardos::bus;
using namespace ardos::kernel::bus;

void Compositor::addContextMenu(ContextMenu* contextMenu, uint32_t pid)
{
    Serial.println("Adding ContextMenu to Compositor");
    if (contextMenu)
    {
        // mWindows[pid].push_back(contextMenu);
        Serial.println("ContextMenu added successfully");
    }
    else
    {
        Serial.println("Failed to add ContextMenu: null pointer");
    }
}

void Compositor::renderContextMenu(ContextMenu* contextMenu, uint32_t pid)
{
    Serial.println("Rendering ContextMenu in Compositor");
    if (contextMenu && contextMenu->isVisible())
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

        const auto& children = contextMenu->GetChildren();
        for (size_t i = 0; i < children.size(); ++i)
        {
            Button* btn = static_cast<Button*>(children[i]);
            // render each button in the context menu
        }
    }
    else
    {
        MessageBus::publish(FILL_RECT_MESSAGE,
                            FillRectMessage(contextMenu->getX(), contextMenu->getY(), contextMenu->getWidth(),
                                            contextMenu->getHeight(), 0x0, pid, MessageType::Display));
    }
}

ContextMenu* Compositor::getContextMenuById(uintptr_t id)
{

    return nullptr;
}