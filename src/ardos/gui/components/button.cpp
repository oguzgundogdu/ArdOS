#include "Arduino.h"
#include <ardos/gui/button.h>
#include <cstdint>

Button::Button(int16_t x, int16_t y, int16_t w, int16_t h, const std::string& label) : Panel(x, y, w, h), mLabel(label)
{
    setZIndex(1);
}

void Button::Init()
{
    auto* eventDispatcher = getEventDispatcher();
    Event event{
        EventType::RenderButton, 0, 0, eventDispatcher->getEventSeq(), this,
    };
    eventDispatcher->dispatch(event);
}

void Button::onBlur(Event& e)
{
}

void Button::onTouch(Event& e)
{
    Serial.println("Button onTouch called");
    if (mCallback)
    {
        mCallback(e);
    }
}