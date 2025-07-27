

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

void Window::Init()
{
    auto* eventDispatcher = getEventDispatcher();
    Event event{
        EventType::RenderWindow, 0, 0, eventDispatcher->getEventSeq(), this,
    };
    eventDispatcher->dispatch(event);

    // Initialize the title bar and close button
    // This can be implemented as needed for rendering the window's title and close button
}
