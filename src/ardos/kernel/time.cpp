#include <ardos/bus/message_bus.h>
#include <ardos/drivers/bus/time_tick_message.h>
#include <ardos/drivers/rtc.h>
#include <ardos/kernel/display.h>
#include <ardos/kernel/power.h>
#include <ardos/kernel/time.h>
#include <ctime>

using namespace ardos::bus;
using namespace ardos::drivers::bus;

TimeManager::TimeManager() : ardos::bus::MessageListener()
{
    MessageBus::subscribe(TIME_TICK_MESSAGE, this);
}

void TimeManager::onMessage(const std::string& topic, const Message& msg)
{
    if (topic == TIME_TICK_MESSAGE)
    {
        TimeTickMessage timeTickMessage = static_cast<const TimeTickMessage&>(msg);
        current_time = timeTickMessage.getTimeInfo();
    }
}

tm TimeManager::getCurrentTime() const
{
    // Return the current time as a tm structure
    return current_time;
}
