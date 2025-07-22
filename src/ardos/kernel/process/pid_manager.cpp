

#include "ardos/kernel/process.h"

namespace ardos::kernel
{
    uint32_t PidManager::nextPid = 1;
    std::vector<uint32_t> PidManager::freePids;

    uint32_t PidManager::allocatePid()
    {
        if (!freePids.empty())
        {
            uint32_t pid = freePids.back();
            freePids.pop_back();
            return pid;
        }
        return nextPid++;
    }

    void PidManager::releasePid(uint32_t pid)
    {
        freePids.push_back(pid);
    }
} // namespace ardos::kernel