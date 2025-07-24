#pragma once

#include "ardos/bus/message_bus.h"
#include <ctime>

class TimeManager : public ardos::bus::MessageListener
{
  public:
    tm getCurrentTime() const;
    void onMessage(const std::string& topic, const ardos::bus::Message& message) override;

    static TimeManager* getInstance()
    {
        static TimeManager instance;
        return &instance;
    }

  private:
    tm current_time;
    TimeManager() = default;
};