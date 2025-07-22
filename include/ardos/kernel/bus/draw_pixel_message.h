#pragma once

#include "ardos/kernel/bus/message_bus.h"

namespace ardos::kernel::bus
{
    class DrawPixelMessage : public Message
    {
      public:
        DrawPixelMessage(int x, int y, uint16_t color, uint32_t source_pid)
            : Message{MessageType::Screen, source_pid}, x(x), y(y), color(color)
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

        uint16_t getColor() const
        {
            return color;
        }

      private:
        int x;
        int y;
        uint16_t color;
    };
} // namespace ardos::kernel::bus