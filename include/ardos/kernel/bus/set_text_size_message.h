#pragma once

#include "ardos/bus/message_bus.h"

#define SET_TEXT_SIZE_MESSAGE "display/setTextSize"

using namespace ardos::bus;

namespace ardos::kernel::bus
{
    class SetTextSizeMessage : public Message
    {
      public:
        SetTextSizeMessage(uint32_t size, uint32_t source_pid, MessageType type) : Message{type, source_pid}, size(size)
        {
        }

      private:
        uint32_t size;
    };
} // namespace ardos::kernel::bus