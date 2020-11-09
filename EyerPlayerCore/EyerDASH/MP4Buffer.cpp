#include "MP4Buffer.hpp"

namespace Eyer
{
    MP4Buffer::MP4Buffer(EyerBuffer & _buffer, MP4BufferType _type)
    {
        buffer = _buffer;
        type = _type;
    }

    MP4Buffer::MP4Buffer(const MP4Buffer & mp4Buffer)
    {
        *this = mp4Buffer;
    }

    MP4Buffer::~MP4Buffer()
    {

    }

    MP4Buffer & MP4Buffer::operator = (const MP4Buffer & mp4Buffer)
    {
        buffer = mp4Buffer.buffer;
        type = mp4Buffer.type;
        return *this;
    }

    EyerBuffer & MP4Buffer::GetBuffer()
    {
        return buffer;
    }

    MP4BufferType MP4Buffer::GetType()
    {
        return type;
    }
}