#include "Arduino.h"
#include "ardos/kernel/state.h"
#include <Wire.h>
#include <ardos/gui/screen_manager.h>
#include <ardos/kernel/event_manager.h>
#include <ardos/kernel/input.h>
#include <ardos/kernel/rtc.h>
#include <ardos/kernel/system.h>

namespace ardos::kernel
{
    bool System::is_initialized = false;
    ScreenManager* System::screenManager = nullptr;

    void System::Start()
    {
        if (!is_initialized)
        {
            Wire.begin();
            RTC::Start();

            Serial.begin(9600);
            Serial.println("ArdOS is starting...");

            screenManager = new ScreenManager();
            screenManager->Start();
            Serial.println("ScreenManager started");

            Serial.println("RTC initialized");

            input::begin();
            Serial.println("Input system initialized");

            ardos::kernel::EventManager::registerListener(screenManager);
            Serial.println("EventManager registered");

            is_initialized = true;
        }
    }

    void System::Poll()
    {
        RTC::Tick(); // Update RTC and dispatch time change events
        input::poll();
        screenManager->Render();
        delay(ardos::kernel::state.is_sleeping
                  ? 1000
                  : 10); // Polling delay
                         // This can be adjusted based on your needs
                         // or replaced with an interrupt-based approach if needed
                         // For example, you could use a timer to call input::poll() at regular
                         // intervals or use a hardware interrupt to trigger input::poll() when a touch
                         // is detected. This is a simple polling loop for demonstration purposes.
    }
} // namespace ardos::kernel