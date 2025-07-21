#include <algorithm>
#include <ardos/kernel/fs/ardfs.h>
#include <sstream>

namespace ardos::kernel::fs
{

    ArdFS::ArdFS()
    {
        root = std::make_shared<FileEntry>();
        root->name = "/";
        root->is_directory = true;
    }

    std::shared_ptr<FileEntry> ArdFS::traverse(const std::string& path) const
    {
        std::istringstream ss(path);
        std::string token;
        std::shared_ptr<FileEntry> current = root;

        while (std::getline(ss, token, '/'))
        {
            if (token.empty())
                continue;
            auto it = std::find_if(current->children.begin(), current->children.end(),
                                   [&](const std::shared_ptr<FileEntry>& e) { return e->name == token; });
            if (it == current->children.end())
                return nullptr;
            current = *it;
        }
        return current;
    }

    std::pair<std::shared_ptr<FileEntry>, std::string> ArdFS::traverseToParent(const std::string& path) const
    {
        std::istringstream ss(path);
        std::string token;
        std::vector<std::string> parts;

        while (std::getline(ss, token, '/'))
        {
            if (!token.empty())
                parts.push_back(token);
        }

        if (parts.empty())
            return {nullptr, ""};
        std::string filename = parts.back();
        parts.pop_back();

        std::string parentPath = "/";
        for (const auto& part : parts)
        {
            parentPath += part + "/";
        }
        if (parentPath.size() > 1)
            parentPath.pop_back();

        return {traverse(parentPath), filename};
    }

    bool ArdFS::createFile(const std::string& path, const std::string& content)
    {
        auto [parent, name] = traverseToParent(path);
        if (!parent || !parent->is_directory)
            return false;

        auto newFile = std::make_shared<FileEntry>();
        newFile->name = name;
        newFile->is_directory = false;
        newFile->content = content;
        parent->children.push_back(newFile);
        return true;
    }

    bool ArdFS::createDirectory(const std::string& path)
    {
        auto [parent, name] = traverseToParent(path);
        if (!parent || !parent->is_directory)
            return false;

        auto newDir = std::make_shared<FileEntry>();
        newDir->name = name;
        newDir->is_directory = true;
        parent->children.push_back(newDir);
        return true;
    }

    bool ArdFS::deleteEntry(const std::string& path)
    {
        auto [parent, name] = traverseToParent(path);
        if (!parent)
            return false;

        auto& children = parent->children;
        auto it = std::remove_if(children.begin(), children.end(),
                                 [&](const std::shared_ptr<FileEntry>& e) { return e->name == name; });
        if (it == children.end())
            return false;
        children.erase(it, children.end());
        return true;
    }

    std::shared_ptr<FileEntry> ArdFS::getEntry(const std::string& path) const
    {
        return traverse(path);
    }

    std::vector<std::string> ArdFS::listDirectory(const std::string& path) const
    {
        auto dir = traverse(path);
        std::vector<std::string> result;
        if (!dir || !dir->is_directory)
            return result;

        for (const auto& entry : dir->children)
        {
            result.push_back(entry->name);
        }
        return result;
    }

} // namespace ardos::kernel::fs
