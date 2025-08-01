#pragma once

#include <map>
#include <string>

namespace ardos::process
{
    class ProcessContext
    {
      public:
        ProcessContext(uint32_t pid) : mPid(pid)
        {
        }
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

        uint32_t getPid() const
        {
            return mPid;
        }

      private:
        uint32_t mPid;
    };
} // namespace ardos::process