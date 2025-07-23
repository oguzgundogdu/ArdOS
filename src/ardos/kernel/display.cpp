#include "ardos/drivers/display.h"
#include <ardos/bus/message_bus.h>
#include <ardos/kernel/bus/draw_line_message.h>
#include <ardos/kernel/bus/draw_pixel_message.h>
#include <ardos/kernel/bus/draw_rect_message.h>
#include <ardos/kernel/bus/fill_rect_message.h>
#include <ardos/kernel/bus/set_cursor_message.h>
#include <ardos/kernel/bus/set_text_color_message.h>
#include <ardos/kernel/bus/set_text_size_message.h>
#include <ardos/kernel/display.h>
#include <ardos/kernel/state.h>
using namespace ardos::bus;
using namespace ardos::kernel::bus;

void DisplayManager::onMessage(const std::string& topic, const ardos::bus::Message& message)
{
    if (((uint16_t)message.getType() & (uint16_t)MessageType::Display) == 0)
        return;
    ardos::drivers::DisplayDriver* driver = ardos::drivers::DisplayDriver::getInstance();
    if (topic == DRAW_PIXEL_MESSAGE)
    {
        DrawPixelMessage msg = static_cast<const DrawPixelMessage&>(message);
        driver->drawPixel(msg.getX(), msg.getY(), msg.getColor());
    }
    else if (topic == DRAW_RECT_MESSAGE)
    {
        DrawRectMessage msg = static_cast<const DrawRectMessage&>(message);
        driver->drawRect(msg.getX(), msg.getY(), msg.getWidth(), msg.getHeight(), msg.getColor());
    }
    else if (topic == DRAW_LINE_MESSAGE)
    {
        DrawLineMessage msg = static_cast<const DrawLineMessage&>(message);
        driver->drawLine(msg.getX1(), msg.getY1(), msg.getX2(), msg.getY2(), msg.getColor());
    }
    else if (topic == FILL_RECT_MESSAGE)
    {
        FillRectMessage msg = static_cast<const FillRectMessage&>(message);
        driver->fillRect(msg.getX(), msg.getY(), msg.getWidth(), msg.getHeight(), msg.getColor());
    }
}