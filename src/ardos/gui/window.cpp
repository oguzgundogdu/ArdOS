#include "Adafruit_ILI9341.h"
#include <ardos/gui/window.h>
#include <ardos/kernel/event_manager.h>

Window::Window(int16_t x, int16_t y, int16_t w, int16_t h, const char *title)
    : Panel(x, y, w, h), title(title) {}

void Window::draw(Adafruit_ILI9341 &tft) {
  tft.fillRect(x, y, width, height, ILI9341_LIGHTGREY);
  tft.drawRect(x, y, width, height, isFocused() ? ILI9341_BLUE : ILI9341_BLACK);

  // title bar
  tft.fillRect(x, y, width, TITLEBAR_HEIGHT, ILI9341_DARKGREY);
  tft.setCursor(x + 2, y + 2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(title);

  int16_t closeBoxX = x + width - 12;
  int16_t closeBoxY = y + 2;

  tft.fillRect(closeBoxX, closeBoxY, 10, 10, ILI9341_RED);
  tft.drawLine(closeBoxX + 2, closeBoxY + 2, closeBoxX + 8, closeBoxY + 8,
               ILI9341_WHITE);
  tft.drawLine(closeBoxX + 8, closeBoxY + 2, closeBoxX + 2, closeBoxY + 8,
               ILI9341_WHITE);
}

void Window::onTouch(int16_t tx, int16_t ty) {
  int16_t closeBoxX = x + width - 12;
  int16_t closeBoxY = y + 2;

  if (tx >= closeBoxX && tx <= closeBoxX + 10 && ty >= closeBoxY &&
      ty <= closeBoxY + 10) {
    ardos::kernel::EventManager::dispatch(
        Event{EventType::Kill, 0, 0, (uintptr_t)this});
    Serial.println("Window is closing");
    return;
  }

  Serial.print("Window touched at: ");
  Serial.print(tx);
  Serial.print(", ");
  Serial.println(ty);
}