#pragma once

#include "ardos/gui/label.h"
#include <ardos/bus/message_bus.h>
#include <ardos/bus/touch_message.h>

#include <ardos/gui/container.h>
#include <ardos/gui/contextmenu.h>
#include <ardos/gui/menubar.h>
#include <ardos/gui/panel.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>
#include <ardos/user/application.h>

using namespace ardos::bus;
using namespace ardos::user;

class Compositor : public Application
{
  public:
    Compositor();
    void onMessage(const std::string& topic, const Message& message) override;
    void run() override;
    void start() override;
    void stop() override;
    static Compositor* GetInstance();

  private:
    std::map<int, std::vector<Panel*>> mPanels;
    Panel* mFocused = nullptr;
    static Compositor* mInstance;

    // Window
    void addWindow(Window* window, uint32_t pid);
    void renderWindow(Window* window, uint32_t pid);
    Window* getWindowById(uintptr_t id);
    void createWindow(uint32_t pid, const char* title, int16_t w, int16_t h);
    void dragWindow(Window* window, int16_t tx, int16_t ty, uint32_t pid);
    void touchWindow(Window* window, int16_t tx, int16_t ty, uint32_t pid);
    void arrangeWindowStack();

    // Panel
    void addPanel(void* panel, uint32_t pid);
    void renderPanel(Panel* panel, uint32_t pid);
    Panel* getPanelById(uintptr_t id);

    // Container
    void renderContainer(Container* container, uint32_t pid);

    // Menubar
    void renderMenuBar(MenuBar* menuBar, uint32_t pid);

    // Context Menu
    void renderContextMenu(ContextMenu* contextMenu, uint32_t pid);

    // Button
    void renderButton(Button* button, uint32_t pid);

    // Label
    void renderLabel(Label* label, uint32_t pid);

    // Event
    void onTouchStart(const TouchMessage& message);
    void onTouchMove(const TouchMessage& message);
    void onTouchEnd(const TouchMessage& message);
    void onKill(const Event& e);
};