#pragma once

#include <ardos/process/managed_process.h>

namespace ardos::process
{
    enum class ProcessState
    {
        Created,
        Running,
        Stopped,
        Terminated
    };

    class Process
    {
      public:
        Process(const std::string& name, ProcessContext* context, ManagedProcess* app);
        void start(); // Starts the process by calling its entrypoint function
        void stop();
        uint32_t getPid() const;
        ProcessState getState() const;
        ProcessContext* getContext() const;
        const std::string& getName() const;
        void tick();

      private:
        uint32_t pid;
        ProcessState state;
        ProcessContext* context;
        ManagedProcess* app;
        std::string name;
    };
} // namespace ardos::process