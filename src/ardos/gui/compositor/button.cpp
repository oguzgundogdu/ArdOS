#include <ardos/bus/message_bus.h>
#include <ardos/gui/compositor.h>
#include <ardos/kernel/bus/print_message.h>
#include <ardos/kernel/bus/set_cursor_message.h>

using namespace ardos::bus;
using namespace ardos::kernel::bus;

void Compositor::renderButton(Button* button, uint32_t pid)
{
    if (button)
    {
        renderPanel(button, pid);
        if (button->isVisible())
        {
            MessageBus::publish(SET_CURSOR_MESSAGE,
                                SetCursorMessage(button->getX() + 4, button->getY() + (button->getHeight() / 2) - 4,
                                                 pid, MessageType::Display));

            MessageBus::publish(PRINT_MESSAGE, PrintMessage(button->GetLabel().c_str(), pid, MessageType::Display));
        }
    }
}
