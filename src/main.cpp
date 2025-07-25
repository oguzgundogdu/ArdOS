#include "ardos/kernel/kernel.h"
#include "ardos/platform/serial_log_handler.h"
#include <Arduino.h>
#include <ardos/process/app_registry.h>

using namespace ardos::kernel;

Kernel* kernel = Kernel::getInstance();

void setup()
{
    ardos::platform::SerialLogHandler::Init();
    kernel->start();
}

void loop()
{
    kernel->run();
}