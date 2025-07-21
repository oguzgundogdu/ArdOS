#include <algorithm>
#include <ardos/kernel/fs/file.h>
#include <cstring>

namespace ardos::kernel::fs
{

    File::File(const std::string& name) : FsNode(name)
    {
    }

    size_t File::write(const uint8_t* data, size_t size, size_t offset)
    {
        if (offset + size > _data.size())
        {
            _data.resize(offset + size);
        }
        std::memcpy(&_data[offset], data, size);
        return size;
    }

    size_t File::read(uint8_t* buffer, size_t size, size_t offset) const
    {
        if (offset >= _data.size())
        {
            return 0;
        }
        size_t read_size = std::min(size, _data.size() - offset);
        std::memcpy(buffer, &_data[offset], read_size);
        return read_size;
    }

    size_t File::size() const
    {
        return _data.size();
    }

    const std::vector<uint8_t>& File::content() const
    {
        return _data;
    }

} // namespace ardos::kernel::fs