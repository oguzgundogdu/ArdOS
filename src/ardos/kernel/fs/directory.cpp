#include <algorithm>
#include <ardos/kernel/fs/directory.h>

namespace ardos::kernel::fs
{
    Directory::Directory(const std::string& name) : FsNode(name)
    {
    }
    bool Directory::addChild(FsNode* child)
    {
        children.push_back(child);
        return true;
    }

    bool Directory::removeChild(const std::string& name)
    {
        auto it = std::find_if(children.begin(), children.end(),
                               [&name](const FsNode* child) { return child->getName() == name; });
        if (it != children.end())
        {
            children.erase(it);
            return true;
        }
        return false;
    }

    FsNode* Directory::getChild(const std::string& name) const
    {
        for (const auto& child : children)
        {
            if (child->getName() == name)
            {
                return child;
            }
        }
        return nullptr;
    }

    const std::vector<FsNode*>& Directory::getChildren() const
    {
        return children;
    }

} // namespace ardos::kernel::fs