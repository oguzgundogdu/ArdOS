

#include "ardos/kernel/process.h"
#include <algorithm>

namespace ardos::kernel
{

    std::vector<Process*> ProcessManager::processes;

    void ProcessManager::addProcess(Process* proc)
    {
        processes.push_back(proc);
    }

    void ProcessManager::removeProcess(uint32_t pid)
    {
        auto it = std::remove_if(processes.begin(), processes.end(), [pid](Process* p) { return p->getPid() == pid; });
        if (it != processes.end())
        {
            processes.erase(it, processes.end());
        }
    }

    Process* ProcessManager::getProcess(uint32_t pid)
    {
        for (auto* proc : processes)
        {
            if (proc->getPid() == pid)
            {
                return proc;
            }
        }
        return nullptr;
    }

    const std::vector<Process*>& ProcessManager::list()
    {
        return processes;
    }

    void ProcessManager::tick()
    {
        for (auto* proc : processes)
        {
            if (proc->getState() == ProcessState::Running)
            {
                proc->tick();
            }
        }
    }

} // namespace ardos::kernel