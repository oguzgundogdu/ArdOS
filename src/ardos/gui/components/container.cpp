#include "Arduino.h"
#include <ardos/gui/container.h>

Container::Container(int x, int y, int width, int height) : Panel(x, y, width, height)
{
}

Container::~Container()
{
    Serial.println("Destroying Container");
    for (Panel* child : *mChildren)
    {
        delete child;
    }
    delete mChildren;
}

void Container::AddChild(Panel* panel)
{
    if (panel)
    {
        mChildren->push_back(panel);
    }
}

void Container::RemoveChild(Panel* panel)
{
    if (panel)
    {
        mChildren->erase(std::remove(mChildren->begin(), mChildren->end(), panel), mChildren->end());
    }
}

void Container::onTouch(void* data)
{
    if (!is_visible)
    {
        return;
    }
}

void Container::Init()
{
    Panel::Init();
    for (Panel* child : *mChildren)
    {
        if (child)
        {
            child->Init();
        }
    }
}