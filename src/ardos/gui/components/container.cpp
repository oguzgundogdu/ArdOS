#include "Arduino.h"
#include <ardos/gui/container.h>
#include <ardos/kernel/screen.h>

Container::Container(int x, int y, int width, int height) : Panel(x, y, width, height)
{
}

Container::~Container()
{
    Serial.println("Destroying Container");
    for (Panel* child : *children)
    {
        delete child;
    }
    delete children;
}

void Container::render()
{
    Screen* screen = Screen::getInstance();
    screen->fillRect(x, y, width, height, ILI9341_WHITE);
    for (Panel* child : *children)
    {
        if (child)
        {
            child->render();
        }
    }
}

void Container::addChild(Panel* panel)
{
    if (panel)
    {
        children->push_back(panel);
    }
}

void Container::removeChild(Panel* panel)
{
    if (panel)
    {
        children->erase(std::remove(children->begin(), children->end(), panel), children->end());
    }
}

void Container::onTouch(int16_t tx, int16_t ty)
{
    if (!is_visible)
    {
        return;
    }
    Serial.print("Container touch at: ");
    Serial.print(tx);
    Serial.print(", ");
    Serial.println(ty);

    for (Panel* child : *children)
    {
        if (child && child->contains(tx, ty))
        {
            child->onTouch(tx, ty);
            return;
        }
    }
}