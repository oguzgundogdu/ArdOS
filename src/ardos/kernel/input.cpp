#include "ardos/drivers/input.h"
#include <ardos/bus/message_bus.h>
#include <ardos/bus/touch_message.h>
#include <ardos/kernel/input.h>
#include <ardos/kernel/power.h>
#include <ardos/kernel/time.h>
#include <ctime>

using namespace ardos::bus;
using namespace ardos::kernel;

InputManager::InputManager()
{
    MessageBus::subscribe(TOUCH_START_MESSAGE, this);
    MessageBus::subscribe(TOUCH_MOVE_MESSAGE, this);
    MessageBus::subscribe(TOUCH_END_MESSAGE, this);
}

void InputManager::onMessage(const std::string& topic, const ardos::bus::Message& message)
{
    if (topic == TOUCH_START_MESSAGE)
    {
        handleTouchStart(message);
    }
    else if (topic == TOUCH_MOVE_MESSAGE)
    {
        handleTouchMove(message);
    }
    else if (topic == TOUCH_END_MESSAGE)
    {
        handleTouchEnd(message);
    }
}

void InputManager::handleTouchStart(const ardos::bus::Message& message)
{
    TimeManager* timeManager = TimeManager::getInstance();
    PowerManager* powerManager = PowerManager::getInstance();
    TouchMessage touchMessage = static_cast<const TouchMessage&>(message);
    tm currentTime = timeManager->getCurrentTime();
    long ct = static_cast<long>(mktime(&currentTime));

    if (ct - touchMessage.getLastTouchTime() > SLEEP_TIMEOUT && !powerManager->isSleepMode())
    {
        powerManager->setSleepMode(true);
        powerManager->setPowerSaveMode(false); // Ensure we are not in power-saving mode
    }
    else if (ct - touchMessage.getLastTouchTime() > POWER_SAVE_TIMEOUT && !powerManager->isPowerSaveMode() &&
             !powerManager->isSleepMode())
    {
        powerManager->setPowerSaveMode(true);
    }

    MessageBus::publish(TOUCH_START_MESSAGE, touchMessage);
}

void InputManager::handleTouchMove(const ardos::bus::Message& message)
{
    auto touchMessage = static_cast<const TouchMessage&>(message);
    MessageBus::publish(TOUCH_MOVE_MESSAGE, touchMessage);
}

void InputManager::handleTouchEnd(const ardos::bus::Message& message)
{
    auto touchMessage = static_cast<const TouchMessage&>(message);
    MessageBus::publish(TOUCH_END_MESSAGE, touchMessage);
}