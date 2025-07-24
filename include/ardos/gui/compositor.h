#pragma once

#include <ardos/bus/message_bus.h>

#include <ardos/gui/contextmenu.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>

using namespace ardos::bus;

class Compositor : public MessageListener
{
  public:
    Compositor();
    void Render();
    void onMessage(const std::string& topic, const Message& message) override;
    static Compositor* GetInstance();

  private:
    std::map<int, std::vector<Window*>> mWindows;
    bool mNeedsRedraw = true;
    Window* mFocused = nullptr;

    // Window
    void addWindow(Window* window, uint32_t pid);
    void renderWindow(Window* window, uint32_t pid);
    Window* getWindowById(uintptr_t id);
    void createWindow(uint32_t pid, const char* title, int16_t w, int16_t h);
    void dragWindow(Window* window, int16_t tx, int16_t ty, uint32_t pid);
    void touchWindow(Window* window, int16_t tx, int16_t ty, uint32_t pid);
    void arrangeWindowStack();

    // Panel
    void addPanel(Panel* panel, uint32_t pid);
    void renderPanel(Panel* panel, uint32_t pid);
    Panel* getPanelById(uintptr_t id);

    // Context Menu
    void addContextMenu(ContextMenu* contextMenu, uint32_t pid);
    void renderContextMenu(ContextMenu* contextMenu, uint32_t pid);
    ContextMenu* getContextMenuById(uintptr_t id);

    // Event
    void onTouchStart(const Event& e);
    void onTouchMove(const Event& e);
    void onTouchEnd(const Event& e);
    void onKill(const Event& e);
    void onSleepRequest(const Event& e);
    void onWakeRequest(const Event& e);
    void onPowerSaveRequest(const Event& e);
    static Compositor* Instance;
};