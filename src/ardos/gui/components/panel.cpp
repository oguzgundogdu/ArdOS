

#include <Arduino.h>
#include <ardos/gui/panel.h>
#include <cstdint>

Panel::Panel(int x, int y, int width, int height) : ComponentEventListener(), x(x), y(y), width(width), height(height)
{
}

Panel::~Panel()
{
    Serial.print("Destroying panel");
    setVisible(false);
    Serial.println("Panel destroyed");
}

bool Panel::contains(int px, int py)
{
    Serial.print("Checking if panel contains point: ");
    Serial.print(px);
    Serial.print(", ");
    Serial.println(py);
    // Check if the point is within the panel's bounds
    return (is_visible && px >= x && px < x + width && py >= y && py < y + height);
}

void Panel::onTouch(void* data)
{
    if (mCallback)
        mCallback();
}

bool Panel::intersects(int16_t rx, int16_t ry, int16_t rw, int16_t rh)
{
    return !(x + width < rx || x > rx + rw || y + height < ry || y > ry + rh);
}

void Panel::setVisible(bool visible)
{
    is_visible = visible;
    this->Init(); // Reinitialize the panel to reflect visibility changes
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
        eventDispatcher->dispatch(event);
    }
}
