#include "ardos/drivers/display.h"
#include "ardos/kernel/config.h"
#include <ardos/bus/message_bus.h>
#include <ardos/kernel/bus/draw_line_message.h>
#include <ardos/kernel/bus/draw_pixel_message.h>
#include <ardos/kernel/bus/draw_rect_message.h>
#include <ardos/kernel/bus/fill_rect_message.h>
#include <ardos/kernel/bus/print_message.h>
#include <ardos/kernel/bus/set_cursor_message.h>
#include <ardos/kernel/bus/set_text_color_message.h>
#include <ardos/kernel/bus/set_text_size_message.h>
#include <ardos/kernel/display.h>
#include <ardos/kernel/logger.h>
#include <ardos/kernel/state.h>
using namespace ardos::bus;
using namespace ardos::kernel::bus;
using namespace ardos::kernel;

DisplayManager* DisplayManager::instance = nullptr;

DisplayManager::DisplayManager()
{
    MessageBus::subscribe(DRAW_PIXEL_MESSAGE, this);
    MessageBus::subscribe(DRAW_RECT_MESSAGE, this);
    MessageBus::subscribe(DRAW_LINE_MESSAGE, this);
    MessageBus::subscribe(FILL_RECT_MESSAGE, this);
    MessageBus::subscribe(SET_CURSOR_MESSAGE, this);
    MessageBus::subscribe(SET_TEXT_COLOR_MESSAGE, this);
    MessageBus::subscribe(SET_TEXT_SIZE_MESSAGE, this);
    MessageBus::subscribe(PRINT_MESSAGE, this);

    drawArdosLogo();
    Logger::Log(LogLevel::Info, "DisplayManager initialized");
}

void DisplayManager::onMessage(const std::string& topic, const ardos::bus::Message& message)
{
    Logger::Log(LogLevel::Debug, "DisplayManager received message: " + topic);
    ardos::drivers::DisplayDriver* driver = ardos::drivers::DisplayDriver::getInstance();
    if (topic == DRAW_PIXEL_MESSAGE)
    {
        DrawPixelMessage msg = static_cast<const DrawPixelMessage&>(message);
        Logger::Log(LogLevel::Debug, "Drawing pixel at (" + std::to_string(msg.getX()) + ", " +
                                         std::to_string(msg.getY()) + ") with color " + std::to_string(msg.getColor()));
        driver->drawPixel(msg.getX(), msg.getY(), msg.getColor());
    }
    else if (topic == DRAW_RECT_MESSAGE)
    {
        DrawRectMessage msg = static_cast<const DrawRectMessage&>(message);
        Logger::Log(LogLevel::Debug, "Drawing rectangle at (" + std::to_string(msg.getX()) + ", " +
                                         std::to_string(msg.getY()) + ") with size (" + std::to_string(msg.getWidth()) +
                                         "x" + std::to_string(msg.getHeight()) + ") and color " +
                                         std::to_string(msg.getColor()));
        driver->drawRect(msg.getX(), msg.getY(), msg.getWidth(), msg.getHeight(), msg.getColor());
    }
    else if (topic == DRAW_LINE_MESSAGE)
    {
        DrawLineMessage msg = static_cast<const DrawLineMessage&>(message);
        Logger::Log(LogLevel::Debug, "Drawing line from (" + std::to_string(msg.getX1()) + ", " +
                                         std::to_string(msg.getY1()) + ") to (" + std::to_string(msg.getX2()) + ", " +
                                         std::to_string(msg.getY2()) + ") with color " +
                                         std::to_string(msg.getColor()));
        driver->drawLine(msg.getX1(), msg.getY1(), msg.getX2(), msg.getY2(), msg.getColor());
    }
    else if (topic == FILL_RECT_MESSAGE)
    {
        FillRectMessage msg = static_cast<const FillRectMessage&>(message);
        Logger::Log(LogLevel::Debug, "Filling rectangle at (" + std::to_string(msg.getX()) + ", " +
                                         std::to_string(msg.getY()) + ") with size (" + std::to_string(msg.getWidth()) +
                                         "x" + std::to_string(msg.getHeight()) + ") and color " +
                                         std::to_string(msg.getColor()));
        driver->fillRect(msg.getX(), msg.getY(), msg.getWidth(), msg.getHeight(), msg.getColor());
    }
    else if (topic == SET_CURSOR_MESSAGE)
    {
        SetCursorMessage msg = static_cast<const SetCursorMessage&>(message);
        Logger::Log(LogLevel::Debug, "Setting cursor position to (" + std::to_string(msg.getX()) + ", " +
                                         std::to_string(msg.getY()) + ")");
        driver->setCursor(msg.getX(), msg.getY());
    }
    else if (topic == SET_TEXT_COLOR_MESSAGE)
    {
        SetTextColorMessage msg = static_cast<const SetTextColorMessage&>(message);
        Logger::Log(LogLevel::Debug, "Setting text color to " + std::to_string(msg.getColor()));
        driver->setTextColor(msg.getColor());
    }
    else if (topic == SET_TEXT_SIZE_MESSAGE)
    {
        SetTextSizeMessage msg = static_cast<const SetTextSizeMessage&>(message);
        Logger::Log(LogLevel::Debug, "Setting text size to " + std::to_string(msg.getSize()));
        driver->setTextSize(msg.getSize());
    }
    else if (topic == PRINT_MESSAGE)
    {
        PrintMessage msg = static_cast<const PrintMessage&>(message);
        Logger::Log(LogLevel::Debug, "Printing text: " + std::string(msg.getText()));
        driver->print(msg.getText());
    }
    else
    {
        Logger::Log(LogLevel::Warning, "DisplayManager received unknown message: " + topic);
    }
}

void DisplayManager::drawArdosLogo()
{
    ardos::drivers::DisplayDriver* driver = ardos::drivers::DisplayDriver::getInstance();
    int startX = 40;
    int startY = 60;
    int spacing = 12;
    uint16_t color = ILI9341_WHITE;
    driver->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x0000); // Clear screen
    driver->drawCharLarge('A', startX + spacing * 0, startY, color);
    driver->drawCharLarge('R', startX + spacing * 1, startY, color);
    driver->drawCharLarge('D', startX + spacing * 2, startY, color);
    driver->drawCharLarge('O', startX + spacing * 3, startY, color);
    driver->drawCharLarge('S', startX + spacing * 4, startY, color);
}