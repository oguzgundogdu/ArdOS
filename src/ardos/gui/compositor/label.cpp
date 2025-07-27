#include <ardos/bus/message_bus.h>
#include <ardos/gui/compositor.h>
#include <ardos/gui/label.h>
#include <ardos/kernel/bus/print_message.h>
#include <ardos/kernel/bus/set_cursor_message.h>
#include <ardos/kernel/bus/set_text_color_message.h>
using namespace ardos::bus;
using namespace ardos::kernel::bus;

void Compositor::renderLabel(Label* label, uint32_t pid)
{
    if (!label)
        return;

    if (label->isVisible())
    {
        renderPanel(label, pid);
        MessageBus::publish(SET_TEXT_COLOR_MESSAGE, SetTextColorMessage(label->getColor(), pid, MessageType::Display));
        MessageBus::publish(SET_CURSOR_MESSAGE,
                            SetCursorMessage(label->getX() + 4, label->getY() + (label->getHeight() / 2) - 4, pid,
                                             MessageType::Display));

        MessageBus::publish(PRINT_MESSAGE, PrintMessage(label->GetText().c_str(), pid, MessageType::Display));
    }
}