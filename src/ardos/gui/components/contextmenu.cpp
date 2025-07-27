#include "ardos/gui/button.h"
#include <ardos/gui/contextmenu.h>

ContextMenu::ContextMenu(int16_t x, int16_t y) : Container(x, y, 100, 42)
{
}

void ContextMenu::AddItem(const std::string& label, const Callback& callback)
{
    auto children = GetChildren();
    Button* button = new Button(x, y + children.size() * ITEM_HEIGHT, width, ITEM_HEIGHT, label.c_str());
    button->setBackgroundColor(ILI9341_WHITE);
    button->setBorderColor(ILI9341_BLACK);
    button->setColor(ILI9341_BLACK);
    button->setCallback(callback);
    AddChild(button);
}

void ContextMenu::Init()
{
    auto* eventDispatcher = getEventDispatcher();
    Event event{
        EventType::RenderContextMenu, 0, 0, eventDispatcher->getEventSeq(), this,
    };
    eventDispatcher->dispatch(event);

    for (auto* child : GetChildren())
    {
        if (child)
        {
            child->Init();
        }
    }
}

void ContextMenu::onBlur(Event& e)
{
    if (!isVisible())
        return;

    setVisible(false);
    auto* eventDispatcher = getEventDispatcher();
    Event event{
        EventType::RenderContextMenu, 0, 0, eventDispatcher->getEventSeq(), this,
    };
    eventDispatcher->dispatch(event);
}