#include <ardos/gui/menubar.h>
#include <ardos/kernel/config.h>

MenuBar::MenuBar() : Panel(0, 0, MENU_WIDTH, MENU_HEIGHT)
{
}

void MenuBar::draw(Adafruit_ILI9341& tft)
{
    tft.fillRect(x, y, width, height, MENU_BG_COLOR);
    tft.setCursor(x + 4, y + 4);
    tft.setTextColor(MENU_TEXT_COLOR);
    tft.setTextSize(1);
    tft.print("Menu");

    tft.setCursor(MENU_WIDTH - 40, y + 4);
    tft.print("ArdOS");
}

void MenuBar::onTouch(int16_t tx, int16_t ty)
{
    if (callback)
    {
        callback();
    }
}

void MenuBar::setCallback(std::function<void()> cb)
{
    callback = cb;
}