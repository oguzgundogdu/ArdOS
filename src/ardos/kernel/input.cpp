#include "ardos/drivers/input.h"
#include <ardos/bus/message_bus.h>
#include <ardos/bus/touch_message.h>
#include <ardos/kernel/input.h>
#include <ardos/kernel/power.h>
#include <ardos/kernel/time.h>
#include <ctime>

using namespace ardos::bus;
using namespace ardos::kernel;

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
    MessageBus::subscribe(DRIVER_TOUCH_START_MESSAGE, this);
    MessageBus::subscribe(DRIVER_TOUCH_MOVE_MESSAGE, this);
    MessageBus::subscribe(DRIVER_TOUCH_END_MESSAGE, this);
}

void InputManager::onMessage(const std::string& topic, const ardos::bus::Message& message)
{
    if (topic == DRIVER_TOUCH_START_MESSAGE)
    {
        handleTouchStart(message);
    }
    else if (topic == DRIVER_TOUCH_MOVE_MESSAGE)
    {
        handleTouchMove(message);
    }
    else if (topic == DRIVER_TOUCH_END_MESSAGE)
    {
        handleTouchEnd(message);
    }
}

void InputManager::handleTouchStart(const ardos::bus::Message& message)
{
    TouchMessage touchMessage = static_cast<const TouchMessage&>(message);

    MessageBus::publish(KERNEL_TOUCH_START_MESSAGE, touchMessage);
}

void InputManager::handleTouchMove(const ardos::bus::Message& message)
{
    auto touchMessage = static_cast<const TouchMessage&>(message);
    MessageBus::publish(KERNEL_TOUCH_MOVE_MESSAGE, touchMessage);
}

void InputManager::handleTouchEnd(const ardos::bus::Message& message)
{
    auto touchMessage = static_cast<const TouchMessage&>(message);
    MessageBus::publish(KERNEL_TOUCH_END_MESSAGE, touchMessage);
}

void InputManager::Run()
{
}