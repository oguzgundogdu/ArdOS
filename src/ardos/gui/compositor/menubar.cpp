#include "ardos/gui/menubar.h"
#include "ardos/bus/message_bus.h"
#include "ardos/kernel/bus/fill_rect_message.h"
#include "ardos/kernel/logger.h"
#include <ardos/gui/compositor.h>
#include <ardos/kernel/bus/set_cursor_message.h>
#include <ardos/kernel/bus/set_text_color_message.h>
#include <ardos/kernel/bus/set_text_size_message.h>

using namespace ardos::bus;
using namespace ardos::kernel::bus;

void Compositor::renderMenuBar(MenuBar* menuBar, uint32_t pid)
{
    if (!menuBar)
        return;
    ardos::kernel::Logger::Log(ardos::kernel::LogLevel::Info, "Rendering MenuBar for PID: " + std::to_string(pid));
    if (menuBar->isVisible())
    {
        MessageBus::publish(FILL_RECT_MESSAGE,
                            FillRectMessage(menuBar->getX(), menuBar->getY(), menuBar->getWidth(), menuBar->getHeight(),
                                            menuBar->getBackgroundColor(), pid, MessageType::Display));
        MessageBus::publish(SET_CURSOR_MESSAGE,
                            SetCursorMessage(menuBar->getX() + 4, menuBar->getY() + 4, pid, MessageType::Display));

        MessageBus::publish(SET_TEXT_COLOR_MESSAGE, SetTextColorMessage(MENU_TEXT_COLOR, pid, MessageType::Display));

        MessageBus::publish(SET_TEXT_SIZE_MESSAGE, SetTextSizeMessage(1, pid, MessageType::Display));
    }
}
