#include "ardos/kernel/display.h"
#include <ardos/bus/message_bus.h>
#include <ardos/drivers/display.h>
#include <ardos/kernel/power.h>

using namespace ardos::bus;
using namespace ardos::drivers;

PowerManager::PowerManager()
{
    // Initialize power management settings
}

PowerManager::~PowerManager()
{
    // Clean up power management resources
}

void PowerManager::onMessage(const std::string& topic, const Message& msg)
{
}

void PowerManager::setPowerSaveMode(bool enabled)
{
    DisplayDriver* driver = DisplayDriver::getInstance();

    if (enabled)
    {
        driver->setBrightness(POWER_SAVE_BRIGHTNESS);
        power_save_mode = true;
    }
    else
    {
        driver->setBrightness(DEFAULT_BRIGHTNESS);
        power_save_mode = false;
    }
}

void PowerManager::setSleepMode(bool enabled)
{
    if (enabled)
    {
        DisplayDriver* driver = DisplayDriver::getInstance();
        driver->setBrightness(SLEEP_BRIGHTNESS);
        sleep_mode = true;
        // Additional code to handle sleep mode, like stopping the display updates
    }
    else
    {
        DisplayDriver* driver = DisplayDriver::getInstance();
        driver->setBrightness(DEFAULT_BRIGHTNESS);
        sleep_mode = false;
        // Additional code to handle waking up from sleep mode
    }
}