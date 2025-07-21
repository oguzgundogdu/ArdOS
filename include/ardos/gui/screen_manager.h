#pragma once

#include <Adafruit_ILI9341.h>
#include <ardos/gui/menubar.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>
#include <ardos/kernel/event_listener.h>
#include <vector>

class ScreenManager : public EventListener
{
  public:
    ScreenManager();
    void Render();
    void OnEvent(const Event& e) override;
    void Start();

  private:
    Adafruit_ILI9341* tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    std::vector<Window*> windows;
    bool needs_redraw = true;
    Window* focused = nullptr;
    MenuBar* menubar = new MenuBar();
    void arrangeWindowStack();
    void createWindow(const char* title, int16_t w, int16_t h);
    void addWindow(Window* window);
    Window* getWindowById(uintptr_t id);
    void onTouchStart(const Event& e);
    void onTouchMove(const Event& e);
    void onTouchEnd(const Event& e);
    void onKill(const Event& e);
};