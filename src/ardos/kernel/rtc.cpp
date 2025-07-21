#include "Arduino.h"
#include "ardos/kernel/event_listener.h"
#include <ardos/kernel/event_manager.h>
#include <ardos/kernel/rtc.h>

namespace ardos::kernel
{

    RTC_DS3231* RTC::rtc = nullptr;
    DateTime RTC::last_known = DateTime(2000, 1, 1, 0, 0, 0);

    void RTC::Start()
    {
        if (rtc != nullptr)
        {
            return; // RTC already initialized
        }
        rtc = new RTC_DS3231();
        rtc->begin();
        if (rtc->lostPower())
        {
            rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
    }

    DateTime RTC::Now()
    {
        return rtc->now();
    }

    void RTC::Tick()
    {
        DateTime now = rtc->now();
        if (now.minute() != last_known.minute())
        {
            last_known = now;
            Event e;
            e.type = EventType::TimeChanged;
            EventManager::dispatch(e);
        }
    }

} // namespace ardos::kernel