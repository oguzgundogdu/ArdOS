#include "ardos/drivers/display.h"
#include "Arduino.h"
#include "api/Common.h"
#include <Fonts/FreeMono9pt7b.h>

using namespace ardos::drivers;
namespace
{
    Adafruit_ILI9341* tft = nullptr;
}
DisplayDriver* DisplayDriver::instance = nullptr;

DisplayDriver::DisplayDriver() : width(WIDTH), height(HEIGHT)
{
    tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    instance = this;
}

DisplayDriver::DisplayDriver(int width, int height) : width(width), height(height)
{
    tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    instance = this;
}

void DisplayDriver::start()
{
    Serial.println("Initializing display driver...");
    tft->begin();
    pinMode(TFT_LED, OUTPUT);
    digitalWrite(TFT_LED, HIGH);
    tft->setRotation(1);
    // tft->setFont(&FreeMono9pt7b);
    this->setBrightness(BRIGHTNESS);
    Serial.println("Display driver initialized");
}

void DisplayDriver::stop()
{
    Serial.println("Stopping display driver...");
    if (tft)
    {
        pinMode(TFT_LED, INPUT);
        digitalWrite(TFT_LED, LOW);
        delete tft;
        tft = nullptr;
    }
    Serial.println("Display driver stopped");
}

void DisplayDriver::run()
{
    // This method can be used for periodic updates if needed
}

void DisplayDriver::drawPixel(int x, int y, uint16_t color)
{
    tft->drawPixel(x, y, color);
}

void DisplayDriver::drawRect(int x, int y, int width, int height, uint16_t color)
{
    tft->drawRect(x, y, width, height, color);
}

void DisplayDriver::drawLine(int x1, int y1, int x2, int y2, uint16_t color)
{
    tft->drawLine(x1, y1, x2, y2, color);
}

void DisplayDriver::fillRect(int x, int y, int width, int height, uint16_t color)
{
    tft->fillRect(x, y, width, height, color);
}

void DisplayDriver::drawCharLarge(char c, int x, int y, uint16_t color)
{
    switch (c)
    {
    case 'A':
        tft->fillRect(x + 2, y, 6, 1, color);
        tft->fillRect(x + 1, y + 1, 1, 7, color);
        tft->fillRect(x + 7, y + 1, 1, 7, color);
        tft->fillRect(x + 2, y + 4, 6, 1, color);
        break;
    case 'R':
        tft->fillRect(x, y, 2, 10, color);
        tft->fillRect(x + 2, y, 4, 2, color);
        tft->fillRect(x + 6, y + 2, 2, 2, color);
        tft->fillRect(x + 2, y + 4, 4, 2, color);
        tft->fillRect(x + 6, y + 6, 2, 4, color);
        break;
    case 'D':
        tft->fillRect(x, y, 2, 10, color);
        tft->fillRect(x + 2, y, 4, 2, color);
        tft->fillRect(x + 6, y + 2, 2, 6, color);
        tft->fillRect(x + 2, y + 8, 4, 2, color);
        break;
    case 'O':
        tft->fillRect(x + 1, y, 6, 2, color);
        tft->fillRect(x, y + 2, 2, 6, color);
        tft->fillRect(x + 7, y + 2, 2, 6, color);
        tft->fillRect(x + 1, y + 8, 6, 2, color);
        break;
    case 'S':
        tft->fillRect(x + 1, y, 6, 2, color);
        tft->fillRect(x, y + 2, 2, 2, color);
        tft->fillRect(x + 1, y + 4, 6, 2, color);
        tft->fillRect(x + 7, y + 6, 2, 2, color);
        tft->fillRect(x + 1, y + 8, 6, 2, color);
        break;
    }
}

void DisplayDriver::setBrightness(int brightness)
{
    analogWrite(TFT_LED, brightness);
}

int DisplayDriver::getBrightness() const
{
    return analogRead(TFT_LED);
}

void DisplayDriver::setCursor(int x, int y)
{
    tft->setCursor(x, y);
}

void DisplayDriver::setTextColor(uint16_t color)
{
    tft->setTextColor(color);
}

void DisplayDriver::setTextSize(uint8_t size)
{
    tft->setTextSize(size);
}

void DisplayDriver::print(const char* text)
{
    tft->print(text);
}

DisplayDriver* DisplayDriver::getInstance()
{
    if (!instance)
    {
        instance = new DisplayDriver();
    }
    return instance;
}
