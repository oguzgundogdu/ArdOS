#include <ardos/kernel/fs/directory.h>
#include <ardos/kernel/fs/file.h>
#include <ardos/kernel/fs/fs_manager.h>
#include <ardos/kernel/fs/node.h>
#include <sstream>

namespace ardos::kernel::fs
{

    FsManager::FsManager()
    {
    }

    Directory* FsManager::getRoot() const
    {
        return root;
    }

    std::vector<std::string> FsManager::splitPath(const std::string& path) const
    {
        std::stringstream ss(path);
        std::string segment;
        std::vector<std::string> parts;
        while (std::getline(ss, segment, '/'))
        {
            if (!segment.empty())
                parts.push_back(segment);
        }
        return parts;
    }

    Directory* FsManager::navigateToDirectory(const std::string& path) const
    {
        auto parts = splitPath(path);
        Directory* current = root;
        for (const auto& part : parts)
        {
            auto child = current->getChild(part);
            current = static_cast<Directory*>(child);
            if (!current)
                return nullptr;
        }
        return current;
    }

    Directory* FsManager::navigateToParentDirectory(const std::string& path) const
    {
        auto parts = splitPath(path);
        if (parts.empty())
            return nullptr;
        parts.pop_back(); // remove last part
        std::string parentPath;
        for (const auto& part : parts)
        {
            parentPath += "/" + part;
        }
        return navigateToDirectory(parentPath);
    }

    bool FsManager::createFile(const std::string& path, const std::string& content)
    {
        auto parent = navigateToParentDirectory(path);
        if (!parent)
            return false;
        auto parts = splitPath(path);
        std::string name = parts.back();
        File* file = new File(name);
        file->write(reinterpret_cast<const uint8_t*>(content.data()), content.size());
        return parent->addChild(file);
    }

    File* FsManager::readFile(const std::string& path) const
    {
        auto parent = navigateToParentDirectory(path);
        if (!parent)
            return nullptr;
        auto parts = splitPath(path);
        auto node = parent->getChild(parts.back());
        return static_cast<File*>(node);
    }

    bool FsManager::deleteFile(const std::string& path)
    {
        auto parent = navigateToParentDirectory(path);
        if (!parent)
            return false;
        auto parts = splitPath(path);
        return parent->removeChild(parts.back());
    }

    bool FsManager::createDirectory(const std::string& path)
    {
        auto parent = navigateToParentDirectory(path);
        if (!parent)
            return false;
        auto parts = splitPath(path);
        std::string name = parts.back();
        Directory* dir = new Directory(name);
        return parent->addChild(dir);
    }

    bool FsManager::deleteDirectory(const std::string& path)
    {
        auto parent = navigateToParentDirectory(path);
        if (!parent)
            return false;
        auto parts = splitPath(path);
        return parent->removeChild(parts.back());
    }

} // namespace ardos::kernel::fs