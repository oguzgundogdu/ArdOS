#include "ardos/drivers/serial.h"
#include <Arduino.h>

namespace ardos::drivers
{

    void SerialDriver::start()
    {
        while (!Serial)
            ;
        Serial.begin(250000);
    }

    void SerialDriver::stop()
    {
        Serial.end();
    }

    void SerialDriver::run()
    {
        // This method can be used for periodic updates if needed
    }

    void SerialDriver::Write(const std::string& msg)
    {
        Serial.println(msg.c_str());
    }

} // namespace ardos::drivers