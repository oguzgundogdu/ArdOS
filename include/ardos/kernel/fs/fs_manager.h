#pragma once

#include <ardos/kernel/fs/directory.h>
#include <ardos/kernel/fs/file.h>
#include <string>
#include <vector>

namespace ardos::kernel::fs
{

    class FsManager
    {
      public:
        FsManager();

        Directory* getRoot() const;

        bool createFile(const std::string& path, const std::string& content);
        File* readFile(const std::string& path) const;
        bool deleteFile(const std::string& path);

        bool createDirectory(const std::string& path);
        bool deleteDirectory(const std::string& path);

      private:
        Directory* root;

        std::vector<std::string> splitPath(const std::string& path) const;
        Directory* navigateToDirectory(const std::string& path) const;
        Directory* navigateToParentDirectory(const std::string& path) const;
    };

} // namespace ardos::kernel::fs