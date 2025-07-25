#pragma once

#define DRAW_PIXEL_MESSAGE "display/drawPixel"

#define DEFAULT_BRIGHTNESS 255   // Default brightness for the TFT backlight
#define POWER_SAVE_BRIGHTNESS 50 // Brightness during power save mode
#define SLEEP_BRIGHTNESS 0

#include "ardos/bus/message_bus.h"

class DisplayManager : public ardos::bus::MessageListener
{
  private:
    void drawArdosLogo();
    static DisplayManager* instance;

  public:
    DisplayManager();
    void onMessage(const std::string& topic, const ardos::bus::Message& message) override;
    static DisplayManager* getInstance()
    {
        if (!instance)
        {
            instance = new DisplayManager();
        }
        return instance;
    }
};