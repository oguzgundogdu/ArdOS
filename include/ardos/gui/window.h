#pragma once

#include <Arduino.h>
#include <ardos/gui/panel.h>

constexpr int TITLEBAR_HEIGHT = 12;

class Window : public Panel {
public:
  Window(int16_t x, int16_t y, int16_t w, int16_t h, const char *title);

  void draw(Adafruit_ILI9341 &tft) override;
  void onTouch(int16_t tx, int16_t ty) override;
  void onDrag(int16_t tx, int16_t ty, Adafruit_ILI9341 &tft);

private:
  const char *title;
  bool is_visible = true;
  bool is_dragging = false;
  int16_t drag_offset_x = 0;
  int16_t drag_offset_y = 0;
  int16_t prev_x = -1;
  int16_t prev_y = -1;
};