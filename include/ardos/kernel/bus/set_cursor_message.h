#pragma once

#include "ardos/bus/message_bus.h"

#define SET_CURSOR_MESSAGE "display/setCursor"

using namespace ardos::bus;

namespace ardos::kernel::bus
{
    class SetCursorMessage : public Message
    {
      public:
        SetCursorMessage(int x, int y, uint32_t source_pid, MessageType type) : Message{type, source_pid}, x(x), y(y)
        {
        }

      private:
        int x;
        int y;
    };
} // namespace ardos::kernel::bus