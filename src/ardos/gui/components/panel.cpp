#include <ardos/gui/panel.h>
#include <cstdint>

Panel::Panel(int x, int y, int width, int height) : ComponentEventListener(), x(x), y(y), width(width), height(height)
{
}

Panel::~Panel()
{
    setVisible(false);
}

bool Panel::contains(int px, int py)
{
    // Check if the point is within the panel's bounds
    return (is_visible && px >= x && px < x + width && py >= y && py < y + height);
}

void Panel::onTouch(void* data)
{
}

void Panel::onBlur(void* data)
{
    // Handle blur event if needed
}

bool Panel::intersects(int16_t rx, int16_t ry, int16_t rw, int16_t rh)
{
    return !(x + width < rx || x > rx + rw || y + height < ry || y > ry + rh);
}

void Panel::Init()
{
    auto* eventDispatcher = getEventDispatcher();
    if (eventDispatcher != nullptr)
    {
        Event event;
        event.type = EventType::RenderPanel;
        event.x = x;
        event.y = y;
        event.id = (uintptr_t)this;
        event.data = this;
        eventDispatcher->dispatch(event);
    }
}
