#include "ardos/bus/message_bus.h"
#include "ardos/drivers/display.h"
#include "ardos/gui/container.h"
#include "ardos/gui/contextmenu.h"
#include "ardos/gui/label.h"
#include "ardos/gui/menubar.h"
#include "ardos/gui/panel.h"
#include "ardos/kernel/config.h"
#include "ardos/kernel/input.h"
#include "ardos/kernel/logger.h"
#include "ardos/kernel/process.h"
#include "ardos/process/process.h"
#include "ardos/process/process_context.h"
#include <ardos/bus/touch_message.h>
#include <ardos/gui/bus/render_component_message.h>
#include <ardos/gui/compositor.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/bus/fill_rect_message.h>
#include <ardos/kernel/state.h>
#include <ardos/process/app_registry.h>
#include <cstdint>

using namespace ardos::bus;
using namespace ardos::gui::bus;
using namespace ardos::kernel;

Compositor* Compositor::mInstance = nullptr;

Compositor::Compositor() = default;

void Compositor::start()
{

    // Register for touch messages
    MessageBus::subscribe(KERNEL_TOUCH_START_MESSAGE, this);
    MessageBus::subscribe(KERNEL_TOUCH_MOVE_MESSAGE, this);
    MessageBus::subscribe(KERNEL_TOUCH_END_MESSAGE, this);

    // Register for window messages
    MessageBus::subscribe(RENDER_PANEL_MESSAGE, this);
    MessageBus::subscribe(RENDER_WINDOW_MESSAGE, this);
    MessageBus::subscribe(RENDER_CONTAINER_MESSAGE, this);
    MessageBus::subscribe(RENDER_MENUBAR_MESSAGE, this);
    MessageBus::subscribe(RENDER_CONTEXTMENU_MESSAGE, this);
    MessageBus::subscribe(RENDER_BUTTON_MESSAGE, this);
    MessageBus::subscribe(RENDER_LABEL_MESSAGE, this);
    Logger::Log(LogLevel::Info, "Compositor started");

    ardos::drivers::DisplayDriver* displayDriver = ardos::drivers::DisplayDriver::getInstance();
    displayDriver->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000); // Clear the screen with black
}

void Compositor::stop()
{
    // Unsubscribe from messages
    MessageBus::unsubscribe(KERNEL_TOUCH_START_MESSAGE, this);
    MessageBus::unsubscribe(KERNEL_TOUCH_MOVE_MESSAGE, this);
    MessageBus::unsubscribe(KERNEL_TOUCH_END_MESSAGE, this);

    MessageBus::unsubscribe(RENDER_PANEL_MESSAGE, this);
    MessageBus::unsubscribe(RENDER_WINDOW_MESSAGE, this);
    MessageBus::unsubscribe(RENDER_CONTAINER_MESSAGE, this);
    MessageBus::unsubscribe(RENDER_MENUBAR_MESSAGE, this);
    MessageBus::unsubscribe(RENDER_CONTEXTMENU_MESSAGE, this);
    MessageBus::unsubscribe(RENDER_BUTTON_MESSAGE, this);
    Logger::Log(LogLevel::Info, "Compositor stopped");
}

void Compositor::run()
{
}

void Compositor::onMessage(const std::string& topic, const Message& message)
{
    if (message.getType() == MessageType::Render)
    {
        RenderComponentMessage renderMessage = static_cast<const RenderComponentMessage&>(message);
        addPanel(renderMessage.getComponent(), message.getSourcePid());

        if (topic == RENDER_PANEL_MESSAGE)
        {
            Panel* obj = static_cast<Panel*>(renderMessage.getComponent());
            renderPanel(obj, message.getSourcePid());
        }
        else if (topic == RENDER_WINDOW_MESSAGE)
        {
            Window* obj = static_cast<Window*>(renderMessage.getComponent());
            renderWindow(obj, message.getSourcePid());
        }
        else if (topic == RENDER_CONTAINER_MESSAGE)
        {
            Container* obj = static_cast<Container*>(renderMessage.getComponent());
            renderContainer(obj, message.getSourcePid());
        }
        else if (topic == RENDER_MENUBAR_MESSAGE)
        {
            MenuBar* obj = static_cast<MenuBar*>(renderMessage.getComponent());
            renderMenuBar(obj, message.getSourcePid());
        }
        else if (topic == RENDER_CONTEXTMENU_MESSAGE)
        {
            ContextMenu* obj = static_cast<ContextMenu*>(renderMessage.getComponent());
            renderContextMenu(obj, message.getSourcePid());
        }
        else if (topic == RENDER_BUTTON_MESSAGE)
        {
            Button* obj = static_cast<Button*>(renderMessage.getComponent());
            renderButton(obj, message.getSourcePid());
        }
        else if (topic == RENDER_LABEL_MESSAGE)
        {
            Label* obj = static_cast<Label*>(renderMessage.getComponent());
            renderLabel(obj, message.getSourcePid());
        }

        Panel* component = static_cast<Panel*>(renderMessage.getComponent());

        // check for intersected panels and render them
        if (!component->isVisible() &&
            (component->getType() == ObjectType::Container || component->getType() == ObjectType::Window))
        {
            for (auto& [pid, panels] : mPanels)
            {
                for (Panel* p : panels)
                {
                    if ((uintptr_t)p != (uintptr_t)component && p->isVisible() &&
                        p->intersects(component->getX(), component->getY(), component->getWidth(),
                                      component->getHeight()))
                    {
                        p->Init();
                    }
                }
            }
        }
    }
    else if (message.getType() == MessageType::Input)
    {
        if (topic == KERNEL_TOUCH_START_MESSAGE)
        {
            Logger::Log(LogLevel::Debug, "Compositor received touch start message");
            onTouchStart(static_cast<const TouchMessage&>(message));
        }
        else if (topic == KERNEL_TOUCH_MOVE_MESSAGE)
        {
            Logger::Log(LogLevel::Debug, "Compositor received touch move message");
            onTouchMove(static_cast<const TouchMessage&>(message));
        }
        else if (topic == KERNEL_TOUCH_END_MESSAGE)
        {
            Logger::Log(LogLevel::Debug, "Compositor received touch end message");
            onTouchEnd(static_cast<const TouchMessage&>(message));
        }
    }
}

void Compositor::onTouchStart(const TouchMessage& message)
{
    for (auto& [pid, panels] : mPanels)
    {
        bool found = false;
        TouchMessage msgNew = message;
        msgNew.setSourcePid(pid);
        for (Panel* p : panels)
        {
            if (p && p->contains(message.getX(), message.getY()))
            {
                found = true;
                Logger::Log(LogLevel::Debug, "Touch start on panel: " + std::to_string((uintptr_t)p));
                mFocused = p;

                msgNew.addElementId((uintptr_t)p);

                if (p->getType() == ObjectType::Window)
                {
                    Window* window = static_cast<Window*>(p);

                    touchWindow(window, message.getX(), message.getY(), pid);
                }
            }
        }

        MessageBus::publish(TOUCH_START_MESSAGE, msgNew);
    }
}

void Compositor::onTouchMove(const TouchMessage& message)
{
    for (auto& [pid, panels] : mPanels)
    {
        for (Panel* p : panels)
        {
            if (p && p->contains(message.getX(), message.getY()))
            {
                if (p->getType() == ObjectType::Window)
                {
                    Window* window = static_cast<Window*>(p);

                    dragWindow(window, message.getX(), message.getY(), pid);
                }
            }
        }
    }
}

void Compositor::onTouchEnd(const TouchMessage& message)
{
    for (auto& [pid, panels] : mPanels)
    {
        for (Panel* p : panels)
        {
            if (p && p->contains(message.getX(), message.getY()))
            {
                if (p->getType() == ObjectType::Window)
                {
                    Window* window = static_cast<Window*>(p);
                    if (window->isDraging)
                    {
                        window->isDraging = false;
                        window->Init();
                    }
                }
            }
        }
    }
}

void Compositor::onKill(const Event& e)
{
    /*for (auto* p : mWindows)
    {

        if (p == nullptr)
        {
            Serial.println("Kill: Null window found, skipping");
            continue;
        }

        uintptr_t windowPtr = (uintptr_t)p;

        if (e.id != 0 && windowPtr == e.id)
        {
            int16_t px = p->getX();
            int16_t py = p->getY();
            int16_t pw = p->getWidth();
            int16_t ph = p->getHeight();

            // Remove the window from the list
            auto it = std::remove(windows.begin(), windows.end(), p);
            if (it != windows.end())
            {
                windows.erase(it);
                delete p;
                Serial.println("Window removed");

                std::vector<Window*> toRedraw;
                for (auto it = windows.begin(); it != windows.end();)
                {
                    if ((*it)->intersects(px, py, pw, ph))
                    {
                        toRedraw.push_back(*it);
                        it = windows.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
                for (auto* p : toRedraw)
                {
                    windows.push_back(p);
                    p->render();
                }
            }
        }
    }*/
}

void Compositor::addPanel(void* panel, uint32_t pid)
{
    Panel* p = static_cast<Panel*>(panel);
    if (panel == nullptr)
    {
        return;
    }

    if (mPanels.find(pid) == mPanels.end())
    {
        mPanels[pid] = std::vector<Panel*>();
    }

    for (Panel* existingPanel : mPanels[pid])
    {
        if ((uintptr_t)existingPanel == (uintptr_t)p)
        {
            return;
        }
    }

    mPanels[pid].push_back(p);
    mFocused = p;
}

Compositor* Compositor::GetInstance()
{
    if (!mInstance)
    {
        mInstance = new Compositor();
        auto pid = PidManager::allocatePid();
        ProcessContext* context = new ProcessContext(pid);
        Process* process = new Process("Compositor", context, mInstance);
        ProcessManager::addProcess(process);
    }
    return mInstance;
}
