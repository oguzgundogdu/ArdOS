#pragma once

#include "ardos/kernel/bus/message_bus.h"

namespace ardos::kernel::bus
{
    class DrawLineMessage : public Message
    {
      public:
        DrawLineMessage(int x1, int y1, int x2, int y2, uint16_t color, uint32_t source_pid)
            : Message{MessageType::Screen, source_pid}, x1(x1), y1(y1), x2(x2), y2(y2), color(color)
        {
        }

        int getX1() const
        {
            return x1;
        }

        int getY1() const
        {
            return y1;
        }

        int getX2() const
        {
            return x2;
        }

        int getY2() const
        {
            return y2;
        }

        uint16_t getColor() const
        {
            return color;
        }

      private:
        int x1;
        int y1;
        int x2;
        int y2;
        uint16_t color;
    };
} // namespace ardos::kernel::bus