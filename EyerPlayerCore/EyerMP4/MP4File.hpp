#ifndef EYERLIB_MP4FILE_HPP
#define EYERLIB_MP4FILE_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class MP4File {
    public:
        MP4File(EyerBuffer & _buffer);
        ~MP4File();

        int Parse();
    private:
        EyerBuffer buffer;
    };
}

#endif //EYERLIB_MP4FILE_HPP
