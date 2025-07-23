#pragma once
#include "ardos/process/process.h"
#include <vector>

using namespace ardos::process;

namespace ardos::kernel
{

    class PidManager
    {
      public:
        static uint32_t allocatePid();
        static void releasePid(uint32_t pid);

      private:
        static uint32_t nextPid;
        static std::vector<uint32_t> freePids;
    };

    class ProcessManager
    {
      public:
        static void addProcess(Process* proc);
        static void removeProcess(uint32_t pid);
        static Process* getProcess(uint32_t pid);
        static const std::vector<Process*>& list();
        static void tick();

      private:
        static std::vector<Process*> processes;
    };
} // namespace ardos::kernel
