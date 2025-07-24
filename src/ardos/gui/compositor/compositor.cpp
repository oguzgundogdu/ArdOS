#include "ardos/bus/message_bus.h"
#include "ardos/process/process_context.h"
#include <ardos/bus/touch_message.h>
#include <ardos/gui/compositor.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/state.h>

using namespace ardos::bus;

Compositor::Compositor()
{
}

void Compositor::Render()
{
}

void Compositor::start(ProcessContext* context)
{

    // Register for touch messages
    MessageBus::subscribe(TOUCH_START_MESSAGE, this);
    MessageBus::subscribe(TOUCH_MOVE_MESSAGE, this);
    MessageBus::subscribe(TOUCH_END_MESSAGE, this);

    // Register for window messages
    MessageBus::subscribe("render/window", this);
}

void Compositor::stop()
{
}

void Compositor::run()
{
}

void Compositor::onMessage(const std::string& topic, const Message& message)
{
    if (topic == "render/window")
    {
    }
    else if (topic == TOUCH_START_MESSAGE)
    {
        onTouchStart(static_cast<const TouchMessage&>(message));
    }
}

void Compositor::onTouchStart(const TouchMessage& message)
{

    for (auto& [pid, panels] : mPanels)
    {
        for (Panel* p : panels)
        {
            if (p && p->contains(message.getX(), message.getY()))
            {
                mFocused = p;
                p->setFocused(true);
                TouchMessage msgNew = message;
                msgNew.setSourcePid(pid);
                MessageBus::publish(TOUCH_START_MESSAGE, msgNew);
                return;
            }
        }
    }
}

void Compositor::onTouchMove(const Event& e)
{
}

void Compositor::onTouchEnd(const Event& e)
{
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

Compositor* Compositor::GetInstance()
{
    if (!Instance)
    {
        Instance = new Compositor();
    }
    return Instance;
}