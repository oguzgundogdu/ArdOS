#include "ardos/kernel/process.h"
#include "ardos/kernel/system.h"

using namespace ardos::kernel;

void startSystem()
{
    System* system = System::getInstance();
    ProcessContext* systemContext = new ProcessContext();
    Process* systemProcess = new Process("System", systemContext, system);
    ProcessManager::addProcess(systemProcess);
    system->start(systemContext);
}

void startCompositor()
{
    System* system = System::getInstance();
    ProcessContext* compositorContext = new ProcessContext();
    Process* compositorProcess = new Process("Compositor", compositorContext, system);
    ProcessManager::addProcess(compositorProcess);
    system->start(compositorContext);
}

void setup()
{
    startSystem();
    startCompositor();
}

void loop()
{
    ProcessManager::tick();
}