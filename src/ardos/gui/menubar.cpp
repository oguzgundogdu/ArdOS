#include <ardos/gui/menubar.h>
#include <ardos/kernel/config.h>

MenuBar::MenuBar() : Panel(0, 0, 320, 16) {}

void MenuBar::draw(Adafruit_ILI9341 &tft) {
  tft.fillRect(x, y, width, height, ILI9341_NAVY);
  tft.setCursor(x + 4, y + 4);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print("Menu");

  tft.setCursor(290, y + 4);
  tft.print("ArdOS");
}

void MenuBar::onTouch(int16_t tx, int16_t ty) {
  if (callback) {
    callback();
  }
}

void MenuBar::setCallback(std::function<void()> cb) { callback = cb; }