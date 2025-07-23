#include "Adafruit_ILI9341.h"
#include "Arduino.h"

#include "ardos/kernel/bus/fill_rect_message.h"
#include "ardos/kernel/bus/message_bus.h"

#include <ardos/gui/window.h>
#include <ardos/kernel/config.h>
#include <ardos/kernel/event_manager.h>

using namespace ardos::kernel::bus;

Window::Window(int16_t x, int16_t y, int16_t w, int16_t h, const char* title) : Container(x, y, w, h), title(title)
{
    ardos::kernel::bus::MessageBus::publish("window.create", WindowCreateMessage(x, y, w, h, title));
}

void Window::onTouch(int16_t tx, int16_t ty)
{
}

void Window::onDrag(int16_t tx, int16_t ty)
{
}