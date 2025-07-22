#include "Arduino.h"
#include "ardos/kernel/bus/message_bus.h"
#include <ardos/kernel/bus/draw_line_message.h>
#include <ardos/kernel/bus/draw_pixel_message.h>
#include <ardos/kernel/bus/draw_rect_message.h>
#include <ardos/kernel/bus/fill_rect_message.h>
#include <ardos/kernel/config.h>
#include <ardos/kernel/event_manager.h>
#include <ardos/kernel/screen.h>
#include <ardos/kernel/state.h>

using namespace ardos::kernel::bus;

Screen* Screen::instance = nullptr;

Screen::Screen(int width, int height) : width(width), height(height)
{
    tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    instance = this;
}

void Screen::init()
{
    if (!isInitialized)
    {
        Serial.println("Initializing screen...");
        tft->begin();
        pinMode(TFT_LED, OUTPUT);
        digitalWrite(TFT_LED, HIGH);
        tft->setRotation(1);
        this->clear();
        setBrightness(DEFAULT_BRIGHTNESS);

        isInitialized = true;
        Serial.println("Screen initialized");
    }
}

void Screen::clear()
{
    tft->fillScreen(ILI9341_BLACK);
}

void Screen::drawPixel(int x, int y, uint16_t color)
{
    tft->drawPixel(x, y, color);
}

void Screen::drawRect(int x, int y, int width, int height, uint16_t color)
{
    tft->drawRect(x, y, width, height, color);
}

void Screen::drawLine(int x1, int y1, int x2, int y2, uint16_t color)
{
    tft->drawLine(x1, y1, x2, y2, color);
}

void Screen::fillRect(int x, int y, int width, int height, uint16_t color)
{
    tft->fillRect(x, y, width, height, color);
}

void Screen::setBrightness(int brightness)
{
    analogWrite(TFT_LED, brightness);
}

int Screen::getBrightness() const
{
    return analogRead(TFT_LED);
}

void Screen::setCursor(int x, int y)
{
    tft->setCursor(x, y);
}

void Screen::setTextColor(uint16_t color)
{
    tft->setTextColor(color);
}

void Screen::setTextSize(uint8_t size)
{
    tft->setTextSize(size);
}

void Screen::print(const char* text)
{
    tft->print(text);
}

Screen* Screen::getInstance()
{
    return instance;
}

void Screen::onMessage(const std::string& topic, const Message& message)
{
    if (message.getType() != MessageType::Screen)
        return;

    if (topic == "screen/drawPixel")
    {
        DrawPixelMessage msg = static_cast<const DrawPixelMessage&>(message);
        drawPixel(msg.getX(), msg.getY(), msg.getColor());
    }
    else if (topic == "screen/drawRect")
    {
        DrawRectMessage msg = static_cast<const DrawRectMessage&>(message);
        drawRect(msg.getX(), msg.getY(), msg.getWidth(), msg.getHeight(), msg.getColor());
    }
    else if (topic == "screen/drawLine")
    {
        DrawLineMessage msg = static_cast<const DrawLineMessage&>(message);
        drawLine(msg.getX1(), msg.getY1(), msg.getX2(), msg.getY2(), msg.getColor());
    }
    else if (topic == "screen/fillRect")
    {
        FillRectMessage msg = static_cast<const FillRectMessage&>(message);
        fillRect(msg.getX(), msg.getY(), msg.getWidth(), msg.getHeight(), msg.getColor());
    }
    else if (topic == "screen/clear")
    {
        clear();
    }
    else if (topic == "screen/powerSave")
    {
        setPowerSaveMode(true);
    }
    else if (topic == "screen/sleep")
    {
        setSleepMode(true);
    }
}

void Screen::setPowerSaveMode(bool enable)
{
    if (enable)
    {
        setBrightness(POWER_SAVE_BRIGHTNESS);
    }
    else
    {
        setBrightness(DEFAULT_BRIGHTNESS);
    }
}

void Screen::setSleepMode(bool enable)
{
    if (enable)
    {
        setBrightness(SLEEP_BRIGHTNESS);
    }
    else
    {
        setBrightness(DEFAULT_BRIGHTNESS);
    }
}