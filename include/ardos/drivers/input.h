#pragma once
#define T_CS 7
#define TOUCH_START_MESSAGE "touch_start"
#define TOUCH_MOVE_MESSAGE "touch_move"
#define TOUCH_END_MESSAGE "touch_end"
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
        static InputDriver* instance;
    };
} // namespace ardos::drivers
