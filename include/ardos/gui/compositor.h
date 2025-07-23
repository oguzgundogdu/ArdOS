#pragma once

#include <Adafruit_ILI9341.h>
#include <ardos/gui/menubar.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>

class Compositor
{
  public:
    Compositor();
    void Render();
    void OnEvent(const Event& e) override;
    void onMessage(const std::string& topic, const Message& message) override;
    void start(ProcessContext* context) override;
    void stop() override;
    void run() override;
    static Compositor* getInstance();

  private:
    std::map<int, std::vector<Window*>> windows;
    bool needs_redraw = true;
    Window* focused = nullptr;
    MenuBar* menubar = nullptr;

    // Window
    void addWindow(uint32_t pid, Window* window);
    void renderWindow(Window* window);
    Window* getWindowById(uintptr_t id);
    void createWindow(uint32_t pid, const char* title, int16_t w, int16_t h);
    void dragWindow(Window* window, int16_t tx, int16_t ty);
    void touchWindow(Window* window, int16_t tx, int16_t ty);
    void arrangeWindowStack();
    // Event
    void onTouchStart(const Event& e);
    void onTouchMove(const Event& e);
    void onTouchEnd(const Event& e);
    void onKill(const Event& e);
    void onSleepRequest(const Event& e);
    void onWakeRequest(const Event& e);
    void onPowerSaveRequest(const Event& e);
    static Compositor* instance;
};