#ifndef EYERLIB_EYERAVSTREAM_HPP
#define EYERLIB_EYERAVSTREAM_HPP

#include <stdio.h>

namespace Eyer
{
    class EyerAVStreamPrivate;

    class EyerAVStream {
    public:
        EyerAVStream();
        ~EyerAVStream();
    public:
        EyerAVStreamPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVSTREAM_HPP
