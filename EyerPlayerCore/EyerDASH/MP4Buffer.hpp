#ifndef EYERLIB_MP4BUFFER_HPP
#define EYERLIB_MP4BUFFER_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    enum MP4BufferType
    {
        HEAD = 1,
        VIDEO = 2,
        AUDIO = 3
    };

    class MP4Buffer {
    public:
        MP4Buffer(EyerBuffer & buffer, MP4BufferType type);
        MP4Buffer(const MP4Buffer & mp4Buffer);
        ~MP4Buffer();

        MP4Buffer & operator = (const MP4Buffer & mp4Buffer);

        EyerBuffer & GetBuffer();
        MP4BufferType GetType();
    private:
        EyerBuffer buffer;
        MP4BufferType type;
    };
}

#endif //EYERLIB_MP4BUFFER_HPP
