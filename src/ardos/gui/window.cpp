#include "Adafruit_ILI9341.h"
#include "Arduino.h"
#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>
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

  if (ty >= y && ty <= y + 12) {
    is_dragging = true;
    drag_offset_x = tx - x;
    drag_offset_y = ty - y;
  }

  Serial.print("Window touched at: ");
  Serial.print(tx);
  Serial.print(", ");
  Serial.println(ty);
}

void Window::onDrag(int16_t tx, int16_t ty, Adafruit_ILI9341 &tft) {
  if (!is_dragging)
    return;

  int16_t new_x = tx - drag_offset_x;
  int16_t new_y = ty - drag_offset_y;
  Serial.print("Dragging window to: ");
  Serial.print(new_x);
  Serial.print(", ");
  Serial.println(new_y);

  // Check bounds
  if (new_x != x || new_y != y) {
    Serial.println("Updating window position");
    // Ensure the new position is within the screen bounds
    if (new_x < 0)
      new_x = 0;
    if (new_y < 0)
      new_y = 0;
    if (new_x + width > tft.width())
      new_x = tft.width() - width;
    if (new_y + height > tft.height())
      new_y = tft.height() - height;
    // Clear previous position
    tft.fillRect(x, y, width, height, ILI9341_BLACK);

    // Set new position
    prev_x = x;
    prev_y = y;
    x = new_x;
    y = new_y;

    // Redraw
    draw(tft);
  }
}