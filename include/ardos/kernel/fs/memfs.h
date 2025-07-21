#pragma once

#include "node.h"
#include <string>
namespace ardos::kernel::fs
{
    class ArdMemFS
    {
        DirectoryNode* root;

      public:
        void mkdir(const std::string& path);
        void touch(const std::string& path);
        void write(const std::string& path, const std::string& data);
        std::string read(const std::string& path);
        void ls(const std::string& path);
    };
} // namespace ardos::kernel::fs