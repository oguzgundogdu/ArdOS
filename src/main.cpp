#include "ardos/kernel/kernel.h"

using namespace ardos::kernel;

Kernel* kernel = Kernel::getInstance();

void setup()
{
    kernel->start();
}

void loop()
{
    kernel->run();
}