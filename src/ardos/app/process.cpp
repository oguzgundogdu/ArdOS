#include "ardos/kernel/process.h"
#include <ardos/app/desktop.h>
#include <ardos/gui/compositor.h>
#include <ardos/kernel/kernel.h>

void ardos::kernel::Kernel::initializeProcesses()
{
    // Initialize the Compositor process
    Compositor* compositor = new Compositor();
    uint32_t pid = PidManager::allocatePid();
    ProcessContext* context = new ProcessContext(pid);
    Process* process = new Process("Compositor", context, compositor);
    ProcessManager::addProcess(process);

    app::Desktop* desktop = new app::Desktop();
    pid = PidManager::allocatePid();
    context = new ProcessContext(pid);
    process = new Process("Desktop", context, desktop);
    ProcessManager::addProcess(process);
}