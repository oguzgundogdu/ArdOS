#pragma once

// Adjust the include path to the correct relative location
#include "message_bus.h"
#include <cstdint>

#define TOUCH_START_MESSAGE "touch/start"
#define TOUCH_MOVE_MESSAGE "touch/move"
#define TOUCH_END_MESSAGE "touch/end"

namespace ardos::bus
{

    class TouchMessage : public Message
    {
      public:
        TouchMessage(int x, int y, long last_touch_time, MessageType type)
            : Message(type), x(x), y(y), last_touch_time(last_touch_time)
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

        long getLastTouchTime() const
        {
            return last_touch_time;
        }

        void setElementId(uint32_t id)
        {
            mElementId = id;
        }

        uint32_t getElementId() const
        {
            return mElementId;
        }

      private:
        int x;
        int y;
        uint32_t mElementId;
        long last_touch_time;
    };

} // namespace ardos::bus