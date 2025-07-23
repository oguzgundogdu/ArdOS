#pragma once

// Adjust the include path to the correct relative location
#include "../../bus/message_bus.h"

using namespace ardos::bus;

namespace ardos::drivers::bus
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

      private:
        int x;
        int y;
        long last_touch_time;
    };

} // namespace ardos::drivers::bus