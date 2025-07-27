#include "Arduino.h"
#include "ardos/api/kernel.h"
#include "ardos/gui/menubar.h"
#include <ardos/app/desktop.h>
#include <string>

using namespace ardos::app;

Desktop::Desktop() : Application()
{
}

Desktop::~Desktop()
{
    delete mMenuBar;
}

void Desktop::start()
{
    mMenuBar = new MenuBar();
    mMenuBar->Init();
}

void Desktop::stop()
{
    if (mMenuBar)
    {
        delete mMenuBar;
        mMenuBar = nullptr;
    }
}

void Desktop::run()
{
    // Serial.println("Desktop application is running");
    tm currentTime = getCurrentTime();

    // Serial.println(("Current time: " + timeStr).c_str());
    if (mTimeInfo.tm_min != currentTime.tm_min)
    {
        // Initialize time information
        std::string timeStr = std::to_string(currentTime.tm_hour) + ":" + std::to_string(currentTime.tm_min);
        Event event{EventType::TimeChange, 0, 0, getEventDispatcher()->getEventSeq(), &timeStr};
        getEventDispatcher()->dispatch(event);
        mTimeInfo = currentTime;
    }
}
