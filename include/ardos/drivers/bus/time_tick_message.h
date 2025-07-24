#pragma once

// Adjust the include path to the correct relative location
#include "../../bus/message_bus.h"
#include <ctime>

using namespace ardos::bus;

namespace ardos::drivers::bus
{

    class TimeTickMessage : public Message
    {
      public:
        TimeTickMessage(const tm& time_info, MessageType type) : Message(type), time_info(time_info)
        {
        }

        const tm& getTimeInfo() const
        {
            return time_info;
        }

      private:
        tm time_info;
    };

} // namespace ardos::drivers::bus