#pragma once
#define T_CS 7
#define DRIVER_TOUCH_START_MESSAGE "touch/driverstart"
#define DRIVER_TOUCH_MOVE_MESSAGE "touch/drivermove"
#define DRIVER_TOUCH_END_MESSAGE "touch/driverend"
#include "ardos/drivers/driver.h"

namespace ardos::drivers
{
    class InputDriver : public Driver
    {
      public:
        InputDriver();
        ~InputDriver();

        void start() override;
        void stop() override;
        void run() override;
        int getX() const;
        int getY() const;

        static InputDriver* getInstance()
        {
            if (!instance)
            {
                instance = new InputDriver();
            }
            return instance;
        }

      private:
        unsigned long lastTouchCheck = 0;
        static InputDriver* instance;
    };
} // namespace ardos::drivers
