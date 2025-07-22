#include <Arduino.h>
#include <ardos/gui/panel.h>
#include <ardos/kernel/screen.h>

Panel::Panel(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
{
}

Panel::~Panel()
{
    Serial.print("Destroying panel");
    setVisible(false);
    Serial.println("Panel destroyed");
};

bool Panel::contains(int px, int py)
{
    Serial.print("Checking if panel contains point: ");
    Serial.print(px);
    Serial.print(", ");
    Serial.println(py);
    // Check if the point is within the panel's bounds
    return (is_visible && px >= x && px < x + width && py >= y && py < y + height);
}

void Panel::onTouch(int16_t tx, int16_t ty)
{
    if (contains(tx, ty))
    {
        if (mCallback)
            mCallback();
    }
}

void Panel::render()
{
    if (!is_visible)
        return;

    Screen* screen = Screen::getInstance();
    screen->fillRect(x, y, width, height, backgroundColor);
    screen->drawRect(x, y, width, height, borderColor);
    screen->setTextColor(color);
    screen->setTextSize(1);
}

bool Panel::intersects(int16_t rx, int16_t ry, int16_t rw, int16_t rh)
{
    return !(x + width < rx || x > rx + rw || y + height < ry || y > ry + rh);
}

void Panel::setVisible(bool visible)
{
    is_visible = visible;
    if (visible)
    {
        render();
    }
    else
    {
        Screen* screen = Screen::getInstance();
        screen->fillRect(x, y, width, height, ILI9341_BLACK);
    }
}