#include "Arduino.h"
#include <RTClib.h>
#include <Wire.h>
#include <ardos/bus/message_bus.h>
#include <ardos/drivers/bus/time_tick_message.h>
#include <ardos/drivers/rtc.h>

namespace
{
    RTC_DS3231* rtc = nullptr;
}

namespace ardos::drivers
{

    void RTC::start()
    {
        Wire.begin();
        Serial.println("Initializing RTC driver...");
        rtc = new RTC_DS3231();
        rtc->begin();
        if (rtc->lostPower())
        {
            rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
        Serial.println("RTC driver initialized successfully");
    }

    void RTC::stop()
    {
        if (rtc)
        {
            Serial.println("Stopping RTC driver...");
            delete rtc;
            rtc = nullptr;
            Wire.end();
            Serial.println("RTC driver stopped");
        }
    }

    void RTC::run()
    {
        DateTime now = rtc->now();
        tm current_time;
        current_time.tm_year = now.year() - 1900; // tm_year is years since 1900
        current_time.tm_mon = now.month() - 1;    // tm_mon is 0-11
        current_time.tm_mday = now.day();
        current_time.tm_hour = now.hour();
        current_time.tm_min = now.minute();
        current_time.tm_sec = now.second();

        ardos::bus::MessageBus::publish(TIME_TICK_MESSAGE,
                                        drivers::bus::TimeTickMessage(current_time, ardos::bus::MessageType::Time));
    }

} // namespace ardos::drivers