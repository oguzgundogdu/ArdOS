#include "Adafruit_ILI9341.h"
#include "Arduino.h"
#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>
#include <ardos/kernel/event_manager.h>

Window::Window(int16_t x, int16_t y, int16_t w, int16_t h, const char* title) : Panel(x, y, w, h), title(title)
{
}

void Window::draw(Adafruit_ILI9341& tft)
{
    tft.fillRect(x, y, width, height, WINDOW_BG_COLOR);
    tft.drawRect(x, y, width, height, isFocused() ? WINDOW_FOCUS_COLOR : WINDOW_BORDER_COLOR);

    // title bar
    tft.fillRect(x, y, width, WINDOW_TITLEBAR_HEIGHT, WINDOW_TITLEBAR_BG_COLOR);
    tft.setCursor(x + 2, y + 2);
    tft.setTextColor(WINDOW_TITLEBAR_TEXT_COLOR);
    tft.setTextSize(WINDOW_TITLEBAR_TEXT_SIZE);
    tft.print(title);

    int16_t closeBoxX = x + width - WINDOW_CLOSE_BOX_X_MARGIN;
    int16_t closeBoxY = y + WINDOW_CLOSE_BOX_Y_MARGIN;

    tft.fillRect(closeBoxX, closeBoxY, WINDOW_CLOSE_BOX_SIZE, WINDOW_CLOSE_BOX_SIZE, WINDOW_CLOSE_BG_COLOR);
    tft.drawLine(closeBoxX + WINDOW_CLOSE_BOX_X_OFFSET, closeBoxY + WINDOW_CLOSE_BOX_Y_OFFSET,
                 closeBoxX + WINDOW_CLOSE_BOX_X_PADDING, closeBoxY + WINDOW_CLOSE_BOX_Y_PADDING,
                 WINDOW_CLOSE_TEXT_COLOR);
    tft.drawLine(closeBoxX + WINDOW_CLOSE_BOX_X_PADDING, closeBoxY + WINDOW_CLOSE_BOX_Y_OFFSET,
                 closeBoxX + WINDOW_CLOSE_BOX_X_OFFSET, closeBoxY + WINDOW_CLOSE_BOX_Y_PADDING,
                 WINDOW_CLOSE_TEXT_COLOR);
}

void Window::onTouch(int16_t tx, int16_t ty)
{
    int16_t closeBoxX = x + width - WINDOW_CLOSE_BOX_X_MARGIN;
    int16_t closeBoxY = y + WINDOW_CLOSE_BOX_Y_MARGIN;

    if (tx >= closeBoxX && tx <= closeBoxX + WINDOW_CLOSE_BOX_SIZE && ty >= closeBoxY &&
        ty <= closeBoxY + WINDOW_CLOSE_BOX_SIZE)
    {
        is_dragging = false;
        ardos::kernel::EventManager::dispatch(Event{EventType::Kill, 0, 0, (uintptr_t)this});
        Serial.println("Window is closing");
        return;
    }

    if (ty >= y && ty <= y + WINDOW_TITLEBAR_HEIGHT)
    {
        drag_offset_x = tx - x;
        drag_offset_y = ty - y;
        is_dragging = true;
    }

    Serial.print("Window touched at: ");
    Serial.print(tx);
    Serial.print(", ");
    Serial.println(ty);
}

void Window::onDrag(int16_t tx, int16_t ty, Adafruit_ILI9341& tft)
{
    if (!is_dragging)
        return;

    int16_t new_x = tx - drag_offset_x;
    int16_t new_y = ty - drag_offset_y;

    if (new_y <= MENU_HEIGHT)
    {
        new_y = MENU_HEIGHT + 1; // Prevent dragging above the menu bar
    }

    Serial.print("Dragging window to: ");
    Serial.print(new_x);
    Serial.print(", ");
    Serial.println(new_y);

    // Check bounds
    if (new_x != x || new_y != y)
    {
        Serial.println("Updating window position");
        // Ensure the new position is within the screen bounds
        if (new_x < 0)
            new_x = 0;
        if (new_y < 0)
            new_y = 0;
        if (new_x + width > SCREEN_WIDTH)
            new_x = SCREEN_WIDTH - width;
        if (new_y + height > SCREEN_HEIGHT - MENU_HEIGHT)
            new_y = SCREEN_HEIGHT - MENU_HEIGHT - height;
        // Clear previous position
        tft.fillRect(x, y, width, height, ILI9341_BLACK);

        // Set new position
        prev_x = x;
        prev_y = y;
        x = new_x;
        y = new_y;

        // Redraw
        draw(tft);
    }
}