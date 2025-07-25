#pragma once

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
    void Render();
    void onMessage(const std::string& topic, const Message& message) override;
    void run() override;
    void start() override;
    void stop() override;
    static Compositor* GetInstance();
    void OnEvent(const Event& e) override;

  private:
    std::map<int, std::vector<Panel*>> mPanels;
    Panel* mFocused = nullptr;

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

    // Container
    void addContainer(Container* container, uint32_t pid);
    void renderContainer(Container* container, uint32_t pid);
    Container* getContainerById(uintptr_t id);

    // Menubar
    void addMenuBar(MenuBar* menuBar, uint32_t pid);
    void renderMenuBar(MenuBar* menuBar, uint32_t pid);
    MenuBar* getMenuBarById(uintptr_t id);

    // Context Menu
    void addContextMenu(ContextMenu* contextMenu, uint32_t pid);
    void renderContextMenu(ContextMenu* contextMenu, uint32_t pid);
    ContextMenu* getContextMenuById(uintptr_t id);

    // Button
    void addButton(Button* button, uint32_t pid);
    void renderButton(Button* button, uint32_t pid);
    Button* getButtonById(uintptr_t id);

    // Event
    void onTouchStart(const TouchMessage& message);
    void onTouchMove(const Event& e);
    void onTouchEnd(const Event& e);
    void onKill(const Event& e);
    static Compositor* Instance;
};