#include "ardos/drivers/serial.h"
#include <Arduino.h>

namespace ardos::drivers
{

    void SerialDriver::start()
    {
        Serial.begin(9600);
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