#include "Arduino.h"
#include <ardos/gui/button.h>
#include <ardos/kernel/screen.h>

Button::Button(int16_t x, int16_t y, int16_t w, int16_t h, const std::string& label) : Panel(x, y, w, h), label(label)
{
    Serial.print("Creating Button: ");
    Serial.println(label.c_str());
    Serial.println("Button created");
}

void Button::render()
{
    Serial.print("Rendering Button: ");
    Serial.println(label.c_str());
    Screen* screen = Screen::getInstance();
    Panel::render();

    screen->setCursor(x + 4, y + (height / 2) - 4);

    screen->print(label.c_str());
    Serial.println("Button rendered");
}