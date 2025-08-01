

#include "ardos/kernel/logger.h"
#include "ardos/kernel/process.h"
#include <algorithm>

namespace ardos::kernel
{
    Process* ProcessManager::mCurrentProcess = nullptr;
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
                setCurrentProcess(proc);
                proc->tick();
            }
        }
    }

    void ProcessManager::initialize()
    {
        Logger::Log(LogLevel::Info, "Initializing ProcessManager");

        if (processes.empty())
        {
            Logger::Log(LogLevel::Warning, "No processes to initialize");
            return;
        }

        for (auto* proc : processes)
        {
            Logger::Log(LogLevel::Info, "Initializing process: " + proc->getName());
            setCurrentProcess(proc);
            proc->start();
            Logger::Log(LogLevel::Info, "Process initialized: " + proc->getName());
        }

        Logger::Log(LogLevel::Info, "ProcessManager initialized");
    }

    Process* ProcessManager::getCurrentProcess()
    {
        return mCurrentProcess;
    }

    void ProcessManager::setCurrentProcess(Process* proc)
    {
        mCurrentProcess = proc;
    }

} // namespace ardos::kernel