#include "ardos/drivers/display.h"
#include "ardos/drivers/input.h"
#include "ardos/drivers/rtc.h"
#include "ardos/drivers/serial.h"
#include "ardos/kernel/display.h"
#include "ardos/kernel/input.h"
#include "ardos/kernel/process.h"
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
    initializeManagers();
    initializeProcesses();

    ProcessManager::initialize();
}

void Kernel::stop()
{
    // Stop the kernel
    // This could include stopping all processes, cleaning up resources, etc.
}

void Kernel::run()
{
    drivers::RTC* rtcDriver = RTC::getInstance();
    rtcDriver->run();

    drivers::DisplayDriver* displayDriver = drivers::DisplayDriver::getInstance();
    displayDriver->run();

    drivers::InputDriver* inputDriver = drivers::InputDriver::getInstance();
    inputDriver->run();

    ProcessManager::tick();
    yield();
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
    drivers::RTC* rtcDriver = drivers::RTC::getInstance();
    rtcDriver->start();

    drivers::SerialDriver* serialDriver = new drivers::SerialDriver();
    serialDriver->start();

    drivers::DisplayDriver* displayDriver = drivers::DisplayDriver::getInstance();
    displayDriver->start();

    drivers::InputDriver* inputDriver = drivers::InputDriver::getInstance();
    inputDriver->start();
}

void Kernel::initializeManagers()
{
    DisplayManager* displayManager = DisplayManager::getInstance();
    InputManager* inputManager = InputManager::getInstance();
}

Kernel* Kernel::instance = nullptr; // Initialize the static instance pointer