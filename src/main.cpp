#include "ardos/kernel/system.h"

void setup()
{
    ardos::kernel::System::Start();
}

void loop()
{
    ardos::kernel::System::Poll();
}