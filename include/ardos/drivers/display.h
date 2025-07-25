#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <ardos/drivers/driver.h>

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
#define TFT_LED 6
#define BRIGHTNESS 255
#define WIDTH 320
#define HEIGHT 240

namespace ardos::drivers
{
    class DisplayDriver : public Driver
    {
      public:
        DisplayDriver();
        DisplayDriver(int width, int height);
        void run() override;
        void start() override;
        void stop() override;
        void drawPixel(int x, int y, uint16_t color);
        void drawRect(int x, int y, int width, int height, uint16_t color);
        void drawLine(int x1, int y1, int x2, int y2, uint16_t color);
        void drawCharLarge(char c, int x, int y, uint16_t color);
        void fillRect(int x, int y, int width, int height, uint16_t color);
        void setCursor(int x, int y);
        void setTextColor(uint16_t color);
        void setTextSize(uint8_t size);
        void print(const char* text);
        void setBrightness(int brightness);
        int getBrightness() const;
        static DisplayDriver* getInstance();

      private:
        int width;
        int height;
        static DisplayDriver* instance;
    };
} // namespace ardos::drivers