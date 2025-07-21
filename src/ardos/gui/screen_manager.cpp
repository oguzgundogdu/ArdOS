#include "Arduino.h"
#include "ardos/kernel/config.h"
#include <ardos/gui/screen_manager.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/state.h>
#include <cstdint>

ScreenManager::ScreenManager() = default;

void ScreenManager::Start()
{
    tft->begin();
    tft->setRotation(1);
    tft->fillScreen(ILI9341_BLACK);

    menubar->draw(*tft);
    menubar->setCallback(
        [this]()
        {
            Serial.println("Menu bar clicked, creating new window");
            createWindow("New Window", 120, 60);
        });
}

void ScreenManager::Render()
{
    if (!needs_redraw)
        return;
    needs_redraw = false;

    arrangeWindowStack();

    for (auto* p : windows)
    {
        p->draw(*tft);
    }
}

void ScreenManager::OnEvent(const Event& e)
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
        break;
    }
}

void ScreenManager::addWindow(Window* window)
{
    windows.push_back(window);
    Serial.print("Window added: ");
    Serial.println((uintptr_t)window);
    ardos::kernel::state.active_panel_id = (uintptr_t)window;
    focused = window;
    window->setFocused(true);
    needs_redraw = true;
}

void ScreenManager::onTouchStart(const Event& e)
{
    Serial.print("Touch start at: ");
    Serial.print(e.x);
    Serial.print(", ");
    Serial.println(e.y);
    if (menubar->contains(e.x, e.y))
    {
        menubar->onTouch(e.x, e.y);
        needs_redraw = true;
        return;
    }
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

void ScreenManager::onTouchMove(const Event& e)
{
    if (focused)
    {
        focused->onDrag(e.x, e.y, *tft);
    }
}

void ScreenManager::onTouchEnd(const Event& e)
{
}

void ScreenManager::onKill(const Event& e)
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
                Serial.println("Window removed");

                // Clear the area
                tft->fillRect(px, py, pw, ph, ILI9341_BLACK);

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
                    p->draw(*tft);
                }
            }
        }
    }
}

Window* ScreenManager::getWindowById(uintptr_t id)
{
    for (auto* p : windows)
    {
        if ((uintptr_t)p == id)
        {
            return p;
        }
    }
    return nullptr;
}

void ScreenManager::arrangeWindowStack()
{
    for (int i = 0; i < windows.size(); i++)
    {
        Window* p = windows[i];
        if (p != nullptr)
        {
            if (i == windows.size() - 1)
            {
                windows[i]->setFocused(true);
                focused = p;
                ardos::kernel::state.active_panel_id = (uintptr_t)p;
            }
            else
            {
                windows[i]->setFocused(false);
            }
        }
    }
}

void ScreenManager::createWindow(const char* title, int16_t w, int16_t h)
{
    uintptr_t activePanel = ardos::kernel::state.active_panel_id;
    int16_t lastX = 0;
    int16_t lastY = 0;
    if (activePanel != 0)
    {
        Window* activePanelPtr = getWindowById(activePanel);
        if (activePanelPtr)
        {
            lastX = activePanelPtr->getX();
            lastY = activePanelPtr->getY();
        }
    }

    auto targetX = lastX + 20;
    auto targetY = lastY + MENU_HEIGHT * 2;
    if (targetX + 120 > SCREEN_WIDTH)
    {
        targetX = 0;
    }
    if (targetY + 60 > SCREEN_HEIGHT)
    {
        targetY = 0;
    }

    Window* window = new Window(targetX, targetY, w, h, title);
    this->addWindow(window);
}