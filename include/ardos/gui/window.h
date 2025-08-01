#pragma once

#include "Adafruit_ILI9341.h"
#include "ardos/gui/panel.h"
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
constexpr int WINDOW_CLOSE_BORDER_COLOR = ILI9341_RED;
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
    void onTouch(Event&) override;
    void Init() override;
    bool isDraging = false;
    const char* GetTitle() const
    {
        return mTitle;
    }
    void SetTitle(const char* newTitle)
    {
        mTitle = newTitle;
    }
    ObjectType getType() const override
    {
        return ObjectType::Window;
    }

  private:
    const char* mTitle;
};