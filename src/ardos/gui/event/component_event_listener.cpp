#include <ardos/gui/event.h>

using namespace ardos::user::event;
using namespace ardos::gui::event;

void ComponentEventListener::OnEvent(const Event& e)
{
    if (e.type == EventType::Touch)
    {
        onTouch(e.data);
    }
    else
    {
        // Handle other event types if necessary
    }
}