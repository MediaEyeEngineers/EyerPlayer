#ifndef EYERLIB_EYERAVSTREAMPRIVATE_HPP
#define EYERLIB_EYERAVSTREAMPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVStreamPrivate
    {
    public:
        AVCodecParameters * codecpar = nullptr;
        AVRational timebase;
    };
}

#endif //EYERLIB_EYERAVSTREAMPRIVATE_HPP
