#pragma once

#include "ardos/bus/message_bus.h"

#define DRAW_RECT_MESSAGE "display/drawRect"

using namespace ardos::bus;

namespace ardos::kernel::bus
{
    class DrawRectMessage : public Message
    {
      public:
        DrawRectMessage(int x, int y, int width, int height, uint16_t color, uint32_t source_pid, MessageType type)
            : Message{type, source_pid}, x(x), y(y), width(width), height(height), color(color)
        {
        }

        int getX() const
        {
            return x;
        }

        int getY() const
        {
            return y;
        }

        int getWidth() const
        {
            return width;
        }

        int getHeight() const
        {
            return height;
        }

        uint16_t getColor() const
        {
            return color;
        }

      private:
        int x;
        int y;
        int width;
        int height;
        uint16_t color;
    };
} // namespace ardos::kernel::bus