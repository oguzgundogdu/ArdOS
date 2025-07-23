#include "ardos/gui/window.h"
#include "ardos/gui/compositor.h"
#include "ardos/kernel/bus/draw_line_message.h"
#include "ardos/kernel/bus/draw_rect_message.h"
#include "ardos/kernel/bus/fill_rect_message.h"
#include "ardos/kernel/bus/message_bus.h"
#include "ardos/kernel/bus/print_message.h"
#include "ardos/kernel/bus/set_cursor_message.h"
#include "ardos/kernel/bus/set_text_color_message.h"
#include "ardos/kernel/bus/set_text_size_message.h"
#include "ardos/kernel/config.h"
#include "ardos/kernel/state.h"

void Compositor::addWindow(uint32_t pid, Window* window)
{
    windows[pid].push_back(window);
    Serial.print("Window added: ");
    Serial.println((uintptr_t)window);
    ardos::kernel::state.active_panel_id = (uintptr_t)window;
    focused = window;
    window->setFocused(true);
    renderWindow(window);
}

void Compositor::createWindow(uint32_t pid, const char* title, int16_t w, int16_t h)
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
    this->addWindow(pid, window);
}

void Compositor::renderWindow(Window* window)
{
    if (window)
    {
        MessageBus::publish(FILL_RECT_MESSAGE, FillRectMessage(window->getX(), window->getY(), window->getWidth(),
                                                               window->getHeight(), WINDOW_BG_COLOR, 0));

        MessageBus::publish(DRAW_RECT_MESSAGE,
                            DrawRectMessage(window->getX(), window->getY(), window->getWidth(), window->getHeight(),
                                            window->isFocused() ? WINDOW_FOCUS_COLOR : WINDOW_BORDER_COLOR, 0));

        // title bar
        MessageBus::publish(FILL_RECT_MESSAGE, FillRectMessage(window->getX(), window->getY(), window->getWidth(),
                                                               WINDOW_TITLEBAR_HEIGHT, WINDOW_TITLEBAR_BG_COLOR, 0));
        MessageBus::publish(SET_CURSOR_MESSAGE, SetCursorMessage(window->getX() + 2, window->getY() + 2, 0));
        MessageBus::publish(SET_TEXT_COLOR_MESSAGE, SetTextColorMessage(WINDOW_TITLEBAR_TEXT_COLOR, 0));
        MessageBus::publish(SET_TEXT_SIZE_MESSAGE, SetTextSizeMessage(WINDOW_TITLEBAR_TEXT_SIZE, 0));
        MessageBus::publish(PRINT_MESSAGE, PrintMessage(window->getTitle(), 0));

        int16_t closeBoxX = window->getX() + window->getWidth() - WINDOW_CLOSE_BOX_X_MARGIN;
        int16_t closeBoxY = window->getY() + WINDOW_CLOSE_BOX_Y_MARGIN;

        MessageBus::publish(FILL_RECT_MESSAGE, FillRectMessage(closeBoxX, closeBoxY, WINDOW_CLOSE_BOX_SIZE,
                                                               WINDOW_CLOSE_BOX_SIZE, WINDOW_CLOSE_BG_COLOR, 0));
        MessageBus::publish(DRAW_RECT_MESSAGE, DrawRectMessage(closeBoxX, closeBoxY, WINDOW_CLOSE_BOX_SIZE,
                                                               WINDOW_CLOSE_BOX_SIZE, WINDOW_CLOSE_BORDER_COLOR, 0));
        MessageBus::publish(DRAW_LINE_MESSAGE,
                            DrawLineMessage(closeBoxX + WINDOW_CLOSE_BOX_X_OFFSET,
                                            closeBoxY + WINDOW_CLOSE_BOX_Y_OFFSET,
                                            closeBoxX + WINDOW_CLOSE_BOX_X_PADDING,
                                            closeBoxY + WINDOW_CLOSE_BOX_Y_PADDING, WINDOW_CLOSE_TEXT_COLOR, 0));
        MessageBus::publish(DRAW_LINE_MESSAGE,
                            DrawLineMessage(closeBoxX + WINDOW_CLOSE_BOX_X_PADDING,
                                            closeBoxY + WINDOW_CLOSE_BOX_Y_OFFSET,
                                            closeBoxX + WINDOW_CLOSE_BOX_X_OFFSET,
                                            closeBoxY + WINDOW_CLOSE_BOX_Y_PADDING, WINDOW_CLOSE_TEXT_COLOR, 0));
    }
}

Window* Compositor::getWindowById(uintptr_t id)
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

void Compositor::arrangeWindowStack()
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

void Compositor::dragWindow(Window* window, int16_t tx, int16_t ty)
{
    if (!window->isDragging())
        return;

    int16_t new_x = tx - window->getX();
    int16_t new_y = ty - window->getY();

    if (new_y <= MENU_HEIGHT)
    {
        new_y = MENU_HEIGHT + 1; // Prevent dragging above the menu bar
    }

    Serial.print("Dragging window to: ");
    Serial.print(new_x);
    Serial.print(", ");
    Serial.println(new_y);

    // Check bounds
    if (new_x != window->getX() || new_y != window->getY())
    {
        Serial.println("Updating window position");
        // Ensure the new position is within the screen bounds
        if (new_x < 0)
            new_x = 0;
        if (new_y < 0)
            new_y = 0;
        if (new_x + window->getWidth() > SCREEN_WIDTH)
            new_x = SCREEN_WIDTH - window->getWidth();
        if (new_y + window->getHeight() > SCREEN_HEIGHT - MENU_HEIGHT)
            new_y = SCREEN_HEIGHT - MENU_HEIGHT - window->getHeight();
        // Clear previous position
        MessageBus::publish(FILL_RECT_MESSAGE, FillRectMessage(window->getX(), window->getY(), window->getWidth(),
                                                               window->getHeight(), ILI9341_BLACK, 0));

        // Set new position
        // prev_x = window->getX();
        // prev_y = window->getY();

        window->setPosition(new_x, new_y);

        // Redraw
        renderWindow(window);
    }
}

void Compositor::touchWindow(Window* window, int16_t tx, int16_t ty)
{
    if (window->contains(tx, ty))
    {
        int16_t closeBoxX = window->getX() + window->getWidth() - WINDOW_CLOSE_BOX_X_MARGIN;
        int16_t closeBoxY = window->getY() + WINDOW_CLOSE_BOX_Y_MARGIN;

        if (tx >= closeBoxX && tx <= closeBoxX + WINDOW_CLOSE_BOX_SIZE && ty >= closeBoxY &&
            ty <= closeBoxY + WINDOW_CLOSE_BOX_SIZE)
        {
            // is_dragging = false;
            // ardos::kernel::EventManager::dispatch(Event{EventType::Kill, 0, 0, (uintptr_t)this});
            Serial.println("Window is closing");
            return;
        }

        if (ty >= window->getY() && ty <= window->getY() + WINDOW_TITLEBAR_HEIGHT)
        {
            /*drag_offset_x = tx - window->getX();
            drag_offset_y = ty - window->getY();
            is_dragging = true;*/
            dragWindow(window, tx, ty);
        }

        Serial.print("Window touched at: ");
        Serial.print(tx);
        Serial.print(", ");
        Serial.println(ty);
    }
}