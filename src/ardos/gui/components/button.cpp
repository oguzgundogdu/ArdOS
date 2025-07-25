
#include <ardos/gui/button.h>
#include <cstdint>

Button::Button(int16_t x, int16_t y, int16_t w, int16_t h, const std::string& label) : Panel(x, y, w, h), mLabel(label)
{
}

void Button::onTouch(void* data)
{
    if (mCallback)
    {
        mCallback();
    }
}

void Button::Init()
{
    auto* eventDispatcher = getEventDispatcher();

    eventDispatcher->dispatch(Event{
        EventType::RenderButton,
        0,
        0,
        (uintptr_t)this,
        this,
    });
}