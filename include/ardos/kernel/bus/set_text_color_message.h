#pragma once

#include "ardos/bus/message_bus.h"
#include <cstdint>

using namespace ardos::bus;

#define SET_TEXT_COLOR_MESSAGE "display/setTextColor"

namespace ardos::kernel::bus
{
    class SetTextColorMessage : public Message
    {
      public:
        SetTextColorMessage(uint32_t color, uint32_t source_pid, MessageType type)
            : Message{type, source_pid}, color(color)
        {
        }

        uint32_t getColor() const
        {
            return color;
        }

      private:
        uint32_t color;
        int y;
    };
} // namespace ardos::kernel::bus