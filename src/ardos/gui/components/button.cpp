#include "Arduino.h"
#include <ardos/gui/button.h>
#include <ardos/kernel/screen.h>

Button::Button(int16_t x, int16_t y, int16_t w, int16_t h, const std::string& label) : Panel(x, y, w, h), mLabel(label)
{
}

void Button::render()
{
    Screen* screen = Screen::getInstance();
    Panel::render();

    screen->setCursor(x + 4, y + (height / 2) - 4);

    screen->print(mLabel.c_str());
}

void Button::onTouch(void* data)
{
    if (mCallback)
    {
        mCallback(data);
    }
}