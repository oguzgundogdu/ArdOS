#include <ardos/gui/contextmenu.h>
#include <ardos/kernel/screen.h>

ContextMenu::ContextMenu(int16_t x, int16_t y) : Panel(x, y, 100, 0)
{
}

void ContextMenu::addItem(const std::string& label, Callback callback)
{
    items.push_back({label, callback});
    height = items.size() * ITEM_HEIGHT;
}

void ContextMenu::render()
{
    Screen* screen = Screen::getInstance();
    screen->fillRect(x, y, width, height, ILI9341_WHITE);
    screen->drawRect(x, y, width, height, ILI9341_BLACK);
    screen->setTextSize(1);

    for (size_t i = 0; i < items.size(); ++i)
    {
        screen->setCursor(x + 4, y + i * ITEM_HEIGHT + 2);
        screen->setTextColor(ILI9341_BLACK);
        screen->print(items[i].label.c_str());
    }
}

void ContextMenu::onTouch(int16_t tx, int16_t ty)
{
    int index = (ty - y) / ITEM_HEIGHT;
    if (index >= 0 && index < (int)items.size())
    {
        items[index].callback();
    }
}