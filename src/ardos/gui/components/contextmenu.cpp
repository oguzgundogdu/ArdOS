#include "Arduino.h"
#include "ardos/gui/button.h"
#include <ardos/gui/contextmenu.h>
#include <ardos/kernel/screen.h>

ContextMenu::ContextMenu(int16_t x, int16_t y) : Container(x, y, 100, 42)
{
    Serial.println("Creating ContextMenu");
}

void ContextMenu::addItem(const std::string& label, Callback callback)
{
    Serial.print("Adding item to ContextMenu: ");
    Serial.println(label.c_str());
    auto children = getChildren();
    Button* button = new Button(x, y + children.size() * ITEM_HEIGHT, width, ITEM_HEIGHT, label.c_str());
    button->setBackgroundColor(ILI9341_WHITE);
    button->setBorderColor(ILI9341_BLACK);
    button->setColor(ILI9341_BLACK);
    button->setCallback(callback);
    addChild(button);
    Serial.println("Item added to ContextMenu");
}

void ContextMenu::render()
{
    Serial.println("Rendering ContextMenu");
    Screen* screen = Screen::getInstance();

    if (is_visible)
    {
        screen->fillRect(x, y, width, height, ILI9341_WHITE);
        screen->drawRect(x, y, width, height, ILI9341_BLACK);
        screen->setTextSize(1);
        auto children = getChildren();
        for (size_t i = 0; i < children.size(); ++i)
        {
            children[i]->render();
        }
    }
    else
    {
        screen->fillRect(x, y, width, height, ILI9341_BLACK);
    }
    Serial.println("ContextMenu rendered");
}