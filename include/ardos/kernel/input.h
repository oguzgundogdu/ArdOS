#pragma once

#include "ardos/bus/message_bus.h"
#include <ctime>

#define KERNEL_TOUCH_START_MESSAGE "touch/kernelstart"
#define KERNEL_TOUCH_MOVE_MESSAGE "touch/kernelmove"
#define KERNEL_TOUCH_END_MESSAGE "touch/kernelend"

namespace ardos::kernel
{
    class InputManager : public ardos::bus::MessageListener
    {
      public:
        InputManager();
        void onMessage(const std::string& topic, const ardos::bus::Message& message) override;
        void Run();

        static InputManager* getInstance()
        {
            if (!instance)
            {
                instance = new InputManager();
            }
            return instance;
        }

      private:
        bool wasTouched = false;
        int16_t last_x = -1;
        int16_t last_y = -1;
        tm last_touch_time;
        static InputManager* instance;
        void handleTouch(const ardos::bus::Message& message);
        void handleTouchStart(const ardos::bus::Message& message);
        void handleTouchMove(const ardos::bus::Message& message);
        void handleTouchEnd(const ardos::bus::Message& message);
    };
} // namespace ardos::kernel