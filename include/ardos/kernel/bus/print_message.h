#pragma once

#include "ardos/bus/message_bus.h"

#define PRINT_MESSAGE "display/print"

using namespace ardos::bus;

namespace ardos::kernel::bus
{
    class PrintMessage : public Message
    {
      public:
        PrintMessage(const char* text, uint32_t source_pid, MessageType type) : Message{type, source_pid}, text(text)
        {
        }

        const char* getText() const
        {
            return text;
        }

      private:
        const char* text;
    };
} // namespace ardos::kernel::bus