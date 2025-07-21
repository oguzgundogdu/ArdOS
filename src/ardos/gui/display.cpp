#include <ardos/gui/display.h>
#include <ardos/kernel/config.h>

void drawMenuBar(Adafruit_ILI9341& tft)
{
    tft.fillRect(0, 0, SCREEN_WIDTH, MENU_HEIGHT, MENU_BG_COLOR);
    tft.setCursor(10, 5);
    tft.setTextColor(MENU_TEXT_COLOR);
    tft.setTextSize(1);
    tft.print("File  Edit  View  Help");

    int16_t x, y;
    uint16_t w, h;
    tft.getTextBounds("ArdOS", 0, 0, &x, &y, &w, &h);
    tft.setCursor(SCREEN_WIDTH - w - 10, 5);
    tft.print("ArdOS");
}
