#include "ardos/drivers/rtc.h"
#include "ardos/kernel/display.h"
#include "ardos/kernel/time.h"
#include <ardos/bus/message_bus.h>
#include <ardos/drivers/bus/time_tick_message.h>
#include <ardos/drivers/display.h>
#include <ardos/drivers/input.h>
#include <ardos/kernel/power.h>

using namespace ardos::bus;
using namespace ardos::drivers;

PowerManager::PowerManager()
{
    MessageBus::subscribe(DRIVER_TOUCH_START_MESSAGE, this);
    MessageBus::subscribe(TIME_TICK_MESSAGE, this);
}

PowerManager::~PowerManager()
{
    // Clean up power management resources
}

void PowerManager::onMessage(const std::string& topic, const Message& msg)
{
    if (topic == DRIVER_TOUCH_START_MESSAGE)
    {
        mLastTouchTime = TimeManager::getInstance()->getCurrentTime(); // Store the last touch time
        if (this->isSleepMode())
        {
            this->setSleepMode(false); // Wake up from sleep mode
        }
        if (this->isPowerSaveMode())
        {
            this->setPowerSaveMode(false); // Disable power save mode on touch
        }
    }
    else if (topic == TIME_TICK_MESSAGE)
    {
        auto m = static_cast<const ardos::drivers::bus::TimeTickMessage&>(msg);

        struct tm timeInfo = m.getTimeInfo();
        long ct = static_cast<long>(mktime(&timeInfo));
        long lastTouchTime = static_cast<long>(mktime(&mLastTouchTime));

        if (ct - lastTouchTime > SLEEP_TIMEOUT && !this->isSleepMode())
        {
            this->setSleepMode(true);
            this->setPowerSaveMode(false); // Ensure we are not in power-saving mode
        }
        else if (ct - lastTouchTime > POWER_SAVE_TIMEOUT && !this->isPowerSaveMode() && !this->isSleepMode())
        {
            this->setPowerSaveMode(true);
        }
    }
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