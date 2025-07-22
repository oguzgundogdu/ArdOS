#include "Arduino.h"
#include "ardos/kernel/state.h"
#include <Wire.h>
#include <ardos/gui/gui_manager.h>
#include <ardos/kernel/event_manager.h>
#include <ardos/kernel/input.h>
#include <ardos/kernel/rtc.h>
#include <ardos/kernel/screen.h>
#include <ardos/kernel/system.h>

namespace ardos::kernel
{
    bool System::is_initialized = false;

    void System::Start()
    {
        if (!is_initialized)
        {
            Wire.begin();
            RTC::Start();

            Serial.begin(9600);
            Serial.println("ArdOS is starting...");
            Screen* screen = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
            screen->init();

            GuiManager* guiManager = GuiManager::getInstance();
            guiManager->Start();

            input::begin();
            Serial.println("Input system initialized");

            is_initialized = true;
            Serial.println("System initialized");
        }
    }

    void System::Poll()
    {
        RTC::Tick(); // Update RTC and dispatch time change events
        input::poll();
        GuiManager::getInstance()->Render();
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