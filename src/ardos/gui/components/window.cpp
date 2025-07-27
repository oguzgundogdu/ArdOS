

#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>

Window::Window(int16_t x, int16_t y, int16_t w, int16_t h, const char* title) : Container(x, y, w, h), mTitle(title)
{
}

void Window::onTouch(Event& e)
{
    if (mCallback)
        mCallback(e);
}
