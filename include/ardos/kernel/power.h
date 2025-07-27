#pragma once

#include "ardos/bus/message_bus.h"

#define SLEEP_TIMEOUT 5 * 60 * 1000  // 5 minutes
#define POWER_SAVE_TIMEOUT 60 * 1000 // 1 minute

class PowerManager : ardos::bus::MessageListener
{
  public:
    PowerManager();
    ~PowerManager();

    void onMessage(const std::string& topic, const ardos::bus::Message& message) override;
    bool isPowerSaveMode() const
    {
        return power_save_mode;
    }
    bool isSleepMode() const
    {
        return sleep_mode;
    }

    void setPowerSaveMode(bool enabled);
    void setSleepMode(bool enabled);

    static PowerManager* getInstance()
    {
        if (!instance)
        {
            instance = new PowerManager();
        }
        return instance;
    }

  private:
    bool power_save_mode = false;
    bool sleep_mode = false;
    static PowerManager* instance;
    tm mLastTouchTime = {};
};