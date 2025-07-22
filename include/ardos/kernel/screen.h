#include "ardos/kernel/event_listener.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

constexpr int DEFAULT_BRIGHTNESS = 255;   // Default brightness for the TFT backlight
constexpr int POWER_SAVE_BRIGHTNESS = 50; // Brightness during power save mode
constexpr int SLEEP_BRIGHTNESS = 0;       // Brightness during sleep mode

class Screen : public EventListener
{
  public:
    Screen(int width, int height);
    void init();
    void clear();
    void drawPixel(int x, int y, uint16_t color);
    void drawRect(int x, int y, int width, int height, uint16_t color);
    void drawLine(int x1, int y1, int x2, int y2, uint16_t color);
    void fillRect(int x, int y, int width, int height, uint16_t color);
    void setCursor(int x, int y);
    void setTextColor(uint16_t color);
    void setTextSize(uint8_t size);
    void print(const char* text);
    void setBrightness(int brightness);
    int getBrightness() const;
    void OnEvent(const Event& e) override;
    static Screen* getInstance();

  private:
    int width;
    int height;
    uint16_t* framebuffer;
    Adafruit_ILI9341* tft;
    bool isInitialized = false;
    static Screen* instance;
    void setPowerSaveMode(bool enable);
    void setSleepMode(bool enable);
};