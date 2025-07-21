#include <ardos/kernel/fs/node.h>
#include <sstream>

namespace ardos::kernel::fs
{

    FileSystem::FileSystem()
    {
        root = new DirectoryNode("/");
    }

    FsNode* FileSystem::getRoot() const
    {
        return root;
    }

    FsNode* FileSystem::find(const std::string& path) const
    {
        if (path == "/")
            return root;

        std::stringstream ss(path);
        std::string segment;
        FsNode* current = root;

        while (std::getline(ss, segment, '/'))
        {
            if (segment.empty())
                continue;

            if (current->isDirectory())
            {
                auto dir = static_cast<DirectoryNode*>(current);
                bool found = false;
                for (const auto& child : dir->getChildren())
                {
                    if (child->getName() == segment)
                    {
                        current = child;
                        found = true;
                        break;
                    }
                }
                if (!found)
                    return nullptr;
            }
            else
            {
                return nullptr;
            }
        }
        return current;
    }

} // namespace ardos::kernel::fs