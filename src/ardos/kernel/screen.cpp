#include <ardos/kernel/config.h>
#include <ardos/kernel/event_manager.h>
#include <ardos/kernel/screen.h>
#include <ardos/kernel/state.h>

Screen* Screen::instance = nullptr;

Screen::Screen(int width, int height) : width(width), height(height)
{
    framebuffer = new uint16_t[width * height];
    tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    instance = this;
}

void Screen::init()
{
    if (!isInitialized)
    {
        tft->begin();
        pinMode(TFT_LED, OUTPUT);
        digitalWrite(TFT_LED, HIGH);
        tft->setRotation(1);
        this->clear();
        setBrightness(DEFAULT_BRIGHTNESS);
        isInitialized = true;
        ardos::kernel::EventManager::registerListener(this);
        Serial.println("Screen initialized");
    }
}

void Screen::clear()
{
    tft->fillScreen(ILI9341_BLACK);
}

void Screen::drawPixel(int x, int y, uint16_t color)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    framebuffer[y * width + x] = color;
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

void Screen::OnEvent(const Event& e)
{
    switch (e.type)
    {
    case EventType::SleepRequest:
        setSleepMode(true);
        break;
    case EventType::WakeRequest:
        setSleepMode(false);
        break;
    case EventType::PowerSaveRequest:
        setPowerSaveMode(true);
        break;
    default:
        break;
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