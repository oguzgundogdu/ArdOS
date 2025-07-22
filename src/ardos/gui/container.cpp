#include <ardos/gui/container.h>
#include <ardos/kernel/screen.h>

Container::Container(int x, int y, int width, int height) : Panel(x, y, width, height)
{
}

void Container::render()
{
    Screen* screen = Screen::getInstance();
    screen->fillRect(x, y, width, height, ILI9341_WHITE);
    for (Panel* child : children)
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
        children.push_back(panel);
    }
}

void Container::removeChild(Panel* panel)
{
    if (panel)
    {
        children.erase(std::remove(children.begin(), children.end(), panel), children.end());
    }
}

void Container::onTouch(int16_t tx, int16_t ty)
{
    for (Panel* child : children)
    {
        if (child && child->contains(tx, ty))
        {
            child->onTouch(tx, ty);
            return;
        }
    }
}