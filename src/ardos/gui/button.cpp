#include <ardos/gui/button.h>
#include <ardos/kernel/screen.h>

Button::Button(int16_t x, int16_t y, int16_t w, int16_t h, const std::string& label) : Panel(x, y, w, h), label(label)
{
}

void Button::render()
{
    Screen* screen = Screen::getInstance();
    screen->fillRect(x, y, width, height, ILI9341_DARKGREY);
    screen->drawRect(x, y, width, height, ILI9341_WHITE);

    screen->setCursor(x + 4, y + (height / 2) - 4);
    screen->setTextColor(ILI9341_WHITE);
    screen->setTextSize(1);
    screen->print(label.c_str());
}