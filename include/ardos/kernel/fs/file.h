#pragma once

#include <ardos/kernel/fs/node.h>
#include <cstdint>
#include <string>
#include <vector>

namespace ardos::kernel::fs
{

    class File : public FsNode
    {
      public:
        File(const std::string& name);

        size_t write(const uint8_t* data, size_t size, size_t offset = 0);
        size_t read(uint8_t* buffer, size_t size, size_t offset = 0) const;

        size_t size() const;
        const std::vector<uint8_t>& content() const;
        bool isDirectory() const override
        {
            return false;
        }

      private:
        std::vector<uint8_t> _data;
    };

} // namespace ardos::kernel::fs