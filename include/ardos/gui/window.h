#pragma once

#include "Adafruit_ILI9341.h"
#include <Arduino.h>
#include <ardos/gui/container.h>

constexpr int WINDOW_BG_COLOR = ILI9341_LIGHTGREY;
constexpr int WINDOW_BORDER_COLOR = ILI9341_BLACK;
constexpr int WINDOW_FOCUS_COLOR = ILI9341_BLUE;
constexpr int WINDOW_TITLEBAR_HEIGHT = 12;
constexpr int WINDOW_TITLEBAR_BG_COLOR = ILI9341_DARKGREY;
constexpr int WINDOW_TITLEBAR_TEXT_COLOR = ILI9341_WHITE;
constexpr int WINDOW_TITLEBAR_TEXT_SIZE = 1;
constexpr int WINDOW_CLOSE_BG_COLOR = ILI9341_RED;
constexpr int WINDOW_CLOSE_TEXT_COLOR = ILI9341_WHITE;
constexpr int WINDOW_CLOSE_BOX_SIZE = 10;
constexpr int WINDOW_CLOSE_BOX_X_OFFSET = 2;
constexpr int WINDOW_CLOSE_BOX_Y_OFFSET = 2;
constexpr int WINDOW_CLOSE_BOX_X_PADDING = 8;
constexpr int WINDOW_CLOSE_BOX_Y_PADDING = 8;
constexpr int WINDOW_CLOSE_BOX_X_MARGIN = 12;
constexpr int WINDOW_CLOSE_BOX_Y_MARGIN = 2;

class Window : public Container
{
  public:
    Window(int16_t x, int16_t y, int16_t w, int16_t h, const char* title);

    void render() override;
    void onTouch(int16_t tx, int16_t ty) override;
    void onDrag(int16_t tx, int16_t ty);

  private:
    const char* title;
    bool is_visible = true;
    bool is_dragging = false;
    int16_t drag_offset_x = 0;
    int16_t drag_offset_y = 0;
    int16_t prev_x = -1;
    int16_t prev_y = -1;
};