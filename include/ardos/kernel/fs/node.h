#pragma once
#include <string>
#include <vector>

namespace ardos::kernel::fs
{
    class FsNode
    {
      protected:
        std::string name;
        FsNode* parent;

      public:
        FsNode(const std::string& name);
        virtual ~FsNode() = default;
        virtual bool isDirectory() const = 0;
        const std::string& getName() const;
    };

    class FileNode : public FsNode
    {
      public:
        FileNode(const std::string& name);
        ~FileNode() override = default;
        bool isDirectory() const override;
    };

    class DirectoryNode : public FsNode
    {
      public:
        DirectoryNode(const std::string& name);
        ~DirectoryNode() override = default;
        bool isDirectory() const override;
        bool addChild(FsNode* child);
        const std::vector<FsNode*>& getChildren() const;

      private:
        std::vector<FsNode*> children;
    };

    class FileSystem
    {
      public:
        FileSystem();

        FsNode* getRoot() const;
        FsNode* find(const std::string& path) const;

      private:
        DirectoryNode* root;
    };

} // namespace ardos::kernel::fs
