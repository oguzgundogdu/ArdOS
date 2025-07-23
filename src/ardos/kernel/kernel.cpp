#include "ardos/drivers/display.h"
#include "ardos/drivers/input.h"
#include "ardos/drivers/rtc.h"
#include <ardos/kernel/kernel.h>

using namespace ardos::kernel;
using namespace ardos::drivers;

Kernel::Kernel()
{
    // Initialize kernel components
}

void Kernel::start()
{
    initializeDrivers();
    initializeProcesses();
}

void Kernel::stop()
{
    // Stop the kernel
    // This could include stopping all processes, cleaning up resources, etc.
}

void Kernel::run()
{
    drivers::RTC* rtcDriver = new drivers::RTC();
    rtcDriver->run();

    drivers::DisplayDriver* displayDriver = drivers::DisplayDriver::getInstance();
    displayDriver->run();
}

Kernel* Kernel::getInstance()
{
    if (!instance)
    {
        instance = new Kernel();
    }
    return instance;
}

void Kernel::initializeDrivers()
{
    drivers::RTC* rtcDriver = new drivers::RTC();
    rtcDriver->start();

    drivers::DisplayDriver* displayDriver = drivers::DisplayDriver::getInstance();
    displayDriver->start();

    drivers::InputDriver* inputDriver = drivers::InputDriver::getInstance();
    inputDriver->start();
}

void Kernel::initializeProcesses()
{
    // Initialize system processes
    // This could include creating the system process, compositor, etc.
}

Kernel* Kernel::instance = nullptr; // Initialize the static instance pointer