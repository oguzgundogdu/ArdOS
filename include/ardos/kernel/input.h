#pragma once

#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <ardos/kernel/event_listener.h>

namespace input
{
    void begin();
    void poll();
    void registerListener(EventListener* listener);
} // namespace input