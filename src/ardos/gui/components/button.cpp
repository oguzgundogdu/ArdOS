
#include <ardos/gui/button.h>

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