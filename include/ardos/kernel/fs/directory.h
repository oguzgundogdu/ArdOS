#pragma once

#include <ardos/kernel/fs/node.h>
#include <string>
#include <vector>

namespace ardos::kernel::fs
{

    class Directory : public FsNode
    {
      public:
        Directory(const std::string& name);

        bool addChild(FsNode* child);
        bool removeChild(const std::string& name);
        FsNode* getChild(const std::string& name) const;
        const std::vector<FsNode*>& getChildren() const;
        bool isDirectory() const override
        {
            return true;
        }

      private:
        std::vector<FsNode*> children;
    };

} // namespace ardos::kernel::fs