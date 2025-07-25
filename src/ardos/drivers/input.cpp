#include "Arduino.h"
#include "ardos/bus/message_bus.h"
#include <XPT2046_Touchscreen.h>
#include <ardos/bus/touch_message.h>
#include <ardos/drivers/input.h>
#include <ardos/kernel/state.h>

using namespace ardos::bus;

namespace
{
    XPT2046_Touchscreen* ts = nullptr;
    bool wasTouched = false;
    int16_t last_x = -1;
    int16_t last_y = -1;
    long last_touch_time = 0;
} // namespace

namespace ardos::drivers
{
    InputDriver* InputDriver::instance = nullptr;

    InputDriver::InputDriver() = default;

    InputDriver::~InputDriver() = default;

    void InputDriver::start()
    {
        Serial.println("Initializing input driver...");
        ts = new XPT2046_Touchscreen(T_CS);
        if (!ts->begin())
        {
            Serial.println("Failed to initialize touchscreen!");
            return;
        }
        ts->setRotation(3); // landscape mode
        Serial.println("InputDriver initialized successfully");
    }

    void InputDriver::stop()
    {
        Serial.println("Stopping input driver...");
        if (ts)
        {
            delete ts;
            ts = nullptr;
        }

        Serial.println("InputDriver stopped");
    }

    void InputDriver::run()
    {
        bool touching = ts->touched();

        if (touching)
        {
            long last_touch_time = millis();

            TS_Point p = ts->getPoint();
            int16_t screenX = map(p.x, 200, 3800, 0, 320);
            int16_t screenY = map(p.y, 200, 3800, 0, 240);

            if (!wasTouched)
            {
                MessageBus::publish(TOUCH_START_MESSAGE, TouchMessage(ts->getPoint().x, ts->getPoint().y,
                                                                      last_touch_time, MessageType::Input));
                wasTouched = true;
            }
            else
            {
                if (abs(screenX - last_x) > 2 || abs(screenY - last_y) > 2)
                {
                    MessageBus::publish(TOUCH_MOVE_MESSAGE,
                                        TouchMessage(screenX, screenY, last_touch_time, MessageType::Input));
                }
                else
                {
                    return;
                }
            }

            last_x = screenX;
            last_y = screenY;
        }
        else if (wasTouched)
        {
            wasTouched = false;
            MessageBus::publish(TOUCH_END_MESSAGE, TouchMessage(last_x, last_y, last_touch_time, MessageType::Input));
        }
    }

} // namespace ardos::drivers