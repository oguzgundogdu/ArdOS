#pragma once

#include "ardos/bus/message_bus.h"

#define CREATE_WINDOW_MESSAGE "display/createWindow"

using namespace ardos::bus;

namespace ardos::gui::bus
{
    class CreateWindowMessage : public Message
    {
      public:
        CreateWindowMessage(const char* title, int16_t width, int16_t height, uint32_t source_pid)
            : Message{MessageType::Render, source_pid}, title(title), width(width), height(height)
        {
        }
        const char* getTitle() const
        {
            return title;
        }
        int16_t getWidth() const
        {
            return width;
        }
        int16_t getHeight() const
        {
            return height;
        }

      private:
        const char* title;
        int16_t width;
        int16_t height;
    };
} // namespace ardos::gui::bus