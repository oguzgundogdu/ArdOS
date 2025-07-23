#pragma once

#define DRAW_LINE_MESSAGE "display/drawLine"
#define DRAW_RECT_MESSAGE "display/drawRect"
#define FILL_RECT_MESSAGE "display/fillRect"
#define PRINT_MESSAGE "display/print"
#define SET_CURSOR_MESSAGE "display/setCursor"
#define SET_TEXT_COLOR_MESSAGE "display/setTextColor"
#define SET_TEXT_SIZE_MESSAGE "display/setTextSize"
#define DRAW_PIXEL_MESSAGE "display/drawPixel"

#define DEFAULT_BRIGHTNESS 255   // Default brightness for the TFT backlight
#define POWER_SAVE_BRIGHTNESS 50 // Brightness during power save mode
#define SLEEP_BRIGHTNESS 0

#include "ardos/bus/message_bus.h"

class DisplayManager : public ardos::bus::MessageListener
{
  public:
    void onMessage(const std::string& topic, const ardos::bus::Message& message) override;
};