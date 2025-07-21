// src/ardos/kernel/fs/node.cpp
#include <ardos/kernel/fs/node.h>

namespace ardos::kernel::fs
{

    FsNode::FsNode(const std::string& name) : name(name)
    {
    }

    const std::string& FsNode::getName() const
    {
        return name;
    }

    bool FsNode::isDirectory() const
    {
        return false;
    }

    // FileNode
    FileNode::FileNode(const std::string& name) : FsNode(name)
    {
    }

    // DirectoryNode
    DirectoryNode::DirectoryNode(const std::string& name) : FsNode(name)
    {
    }

    bool DirectoryNode::addChild(FsNode* child)
    {
        children.push_back(child);
        return true;
    }

    const std::vector<FsNode*>& DirectoryNode::getChildren() const
    {
        return children;
    }

    bool DirectoryNode::isDirectory() const
    {
        return true;
    }

} // namespace ardos::kernel::fs
