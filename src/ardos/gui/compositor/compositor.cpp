#include "Arduino.h"

#include "ardos/gui/bus/create_window_message.h"
#include "ardos/kernel/bus/message_bus.h"
#include "ardos/kernel/event_listener.h"
#include "ardos/kernel/event_manager.h"
#include <ardos/gui/compositor.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/state.h>
#include <cstdint>

using namespace ardos::kernel::bus;

Compositor* Compositor::instance = nullptr;

Compositor::Compositor()
{
}

void Compositor::start(ProcessContext* context)
{
    Serial.println("Starting Compositor...");
    menubar = new MenuBar();
    menubar->render();
    ardos::kernel::EventManager::registerListener(this);
    ardos::kernel::bus::MessageBus::subscribe("render", this);
    Serial.println("Compositor started");
    // menubar->setCallback(
    //     [this]()
    //     {
    //         Serial.println("Menu bar clicked, creating new window");
    //         createWindow("New Window", 120, 60);
    //     });
}

void Compositor::stop()
{
    Serial.println("Stopping Compositor...");
    ardos::kernel::EventManager::unregisterListener(this);
    for (auto* window : windows)
    {
        delete window;
    }
    windows.clear();
    delete menubar;
    menubar = nullptr;
    Serial.println("Compositor stopped");
}

void Compositor::run()
{
    Render();
}

void Compositor::Render()
{
    if (!needs_redraw)
        return;
    needs_redraw = false;

    arrangeWindowStack();

    for (auto& [key, windowList] : windows)
    {
        for (auto* p : windowList)
        {
            renderWindow(p);
        }
    }
}

void Compositor::OnEvent(const Event& e)
{
    switch (e.type)
    {
    case EventType::TouchStart:
        onTouchStart(e);
        break;

    case EventType::TouchMove:
        onTouchMove(e);
        break;

    case EventType::TouchEnd:
        onTouchEnd(e);
        break;
    case EventType::Kill:
        onKill(e);
    case EventType::TimeChanged:
        // menubar->render();
        break;
    }
}

void Compositor::onMessage(const std::string& topic, const Message& message)
{
    if (message.getType() != ardos::kernel::bus::MessageType::Render)
        return;

    if (topic == "screen/createWindow")
    {
        auto* createWindowMessage = static_cast<const CreateWindowMessage*>(&message);
        if (createWindowMessage)
        {
            createWindow(createWindowMessage->getTitle(), createWindowMessage->getWidth(),
                         createWindowMessage->getHeight());
        }
    }
}

void Compositor::onTouchStart(const Event& e)
{
    Serial.print("Touch start at: ");
    Serial.print(e.x);
    Serial.print(", ");
    Serial.println(e.y);
    menubar->onTouch(e.x, e.y);
    for (Window* w : windows)
    {
        if (w && w->contains(e.x, e.y))
        {
            windows.erase(std::remove(windows.begin(), windows.end(), w), windows.end());
            windows.push_back(w);
            focused = w;
            w->setFocused(true);
            w->onTouch(e.x, e.y);
            break;
        }
    }
}

void Compositor::onTouchMove(const Event& e)
{
    if (focused)
    {
        focused->onDrag(e.x, e.y);
    }
}

void Compositor::onTouchEnd(const Event& e)
{
}

void Compositor::onKill(const Event& e)
{
    for (auto* p : windows)
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
    }
}

Compositor* Compositor::getInstance()
{
    if (!instance)
    {
        instance = new Compositor();
    }
    return instance;
}