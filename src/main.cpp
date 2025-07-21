#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Arduino.h>
#include <SPI.h>

#include <ardos/gui/screen_manager.h>
#include <ardos/kernel/event_manager.h>
#include <ardos/kernel/input.h>

ScreenManager* screenManager = new ScreenManager();

void setup()
{
    Serial.begin(9600);
    Serial.println("ArdOS is starting...");
    screenManager->Start();
    input::begin();
    ardos::kernel::EventManager::registerListener(screenManager);
}

void loop()
{
    input::poll();
    screenManager->Render();
    delay(10); // Polling delay
               // This can be adjusted based on your needs
               // or replaced with an interrupt-based approach if needed
               // For example, you could use a timer to call input::poll() at regular
               // intervals or use a hardware interrupt to trigger input::poll() when a touch
               // is detected. This is a simple polling loop for demonstration purposes.
}