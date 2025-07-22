#pragma once

#include <Adafruit_ILI9341.h>
#include <ardos/gui/menubar.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>
#include <ardos/kernel/event_listener.h>
#include <ardos/kernel/process.h>
#include <ardos/kernel/screen.h>
#include <vector>

using namespace ardos::kernel;

class Compositor : public EventListener, public Application
{
  public:
    Compositor();
    void Render();
    void OnEvent(const Event& e) override;
    void start(ProcessContext* context) override;
    void stop() override;
    void run() override;
    static Compositor* getInstance();
    void CreateWindow(const char* title, int16_t w, int16_t h);

  private:
    std::vector<Window*> windows;
    bool needs_redraw = true;
    Window* focused = nullptr;
    MenuBar* menubar = nullptr;
    void arrangeWindowStack();

    void addWindow(Window* window);
    Window* getWindowById(uintptr_t id);
    void onTouchStart(const Event& e);
    void onTouchMove(const Event& e);
    void onTouchEnd(const Event& e);
    void onKill(const Event& e);
    void onSleepRequest(const Event& e);
    void onWakeRequest(const Event& e);
    void onPowerSaveRequest(const Event& e);
    static Compositor* instance;
};