#include <ardos/gui/label.h>

Label::Label(const std::string& text, int x, int y, int width, int height) : Panel(x, y, width, height), text(text)
{
}

void Label::Init()
{
    auto* eventDispatcher = getEventDispatcher();
    Event event{
        EventType::RenderLabel, 0, 0, eventDispatcher->getEventSeq(), this,
    };
    eventDispatcher->dispatch(event);
}