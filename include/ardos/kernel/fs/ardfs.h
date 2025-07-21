#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ardos::kernel::fs
{

    struct FileEntry
    {
        std::string name;
        bool is_directory;
        std::vector<std::shared_ptr<FileEntry>> children;
        std::string content;
    };

    class ArdFS
    {
      public:
        ArdFS();

        bool createFile(const std::string& path, const std::string& content = "");
        bool createDirectory(const std::string& path);
        bool deleteEntry(const std::string& path);
        std::shared_ptr<FileEntry> getEntry(const std::string& path) const;
        std::vector<std::string> listDirectory(const std::string& path) const;

      private:
        std::shared_ptr<FileEntry> root;
        std::shared_ptr<FileEntry> traverse(const std::string& path) const;
        std::pair<std::shared_ptr<FileEntry>, std::string> traverseToParent(const std::string& path) const;
    };

} // namespace ardos::kernel::fs