#pragma once

#include <ardos/kernel/time.h>

inline tm getCurrentTime()
{
    return TimeManager::getInstance()->getCurrentTime();
}