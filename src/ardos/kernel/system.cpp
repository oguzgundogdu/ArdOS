#include "Arduino.h"
#include <Wire.h>

#include <ardos/kernel/config.h>
#include <ardos/kernel/event_manager.h>
#include <ardos/kernel/input.h>
#include <ardos/kernel/rtc.h>
#include <ardos/kernel/screen.h>
#include <ardos/kernel/system.h>

namespace ardos::kernel
{
    System* System::instance = nullptr;

    void System::start(ardos::kernel::ProcessContext* context)
    {

        RTC::Start();

        Serial.begin(9600);
        Serial.println("ArdOS is starting...");
        Screen* screen = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
        screen->init();

        input::begin();
        Serial.println("System initialized");
    }

    void System::stop()
    {
        Wire.end();
        Serial.end();
    }

    void System::run()
    {
        RTC::Tick();
        input::poll();
    }
} // namespace ardos::kernel