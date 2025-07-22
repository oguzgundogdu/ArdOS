#pragma once
#include <map>
#include <string>
#include <vector>

namespace ardos::kernel
{
    enum class ProcessState
    {
        Created,
        Running,
        Stopped,
        Terminated
    };

    class PidManager
    {
      public:
        static uint32_t allocatePid();
        static void releasePid(uint32_t pid);

      private:
        static uint32_t nextPid;
        static std::vector<uint32_t> freePids;
    };

    class ProcessContext
    {
      public:
        std::map<std::string, std::string> memory; // Simulated process memory
        // Future: Add isolated file system, event manager etc.

        bool has(const std::string& key) const
        {
            return memory.find(key) != memory.end();
        }

        std::string get(const std::string& key) const
        {
            auto it = memory.find(key);
            if (it != memory.end())
            {
                return it->second;
            }
            return "";
        }

        void set(const std::string& key, const std::string& value)
        {
            memory[key] = value;
        }

        void remove(const std::string& key)
        {
            memory.erase(key);
        }
    };

    class Application
    {
      public:
        virtual void start(ardos::kernel::ProcessContext* context) = 0; // Start the application
        virtual void stop() = 0;                                        // Stop the application
        virtual void run() = 0;                                         // Run the application loop
        virtual ~Application() = default;                               // Virtual destructor for cleanup
    };

    class Process
    {
      public:
        Process(const std::string& name, ProcessContext* context, Application* app);
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
        Application* app;
        std::string name;
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
