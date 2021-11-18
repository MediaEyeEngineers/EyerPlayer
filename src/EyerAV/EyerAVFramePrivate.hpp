#ifndef EYERLIB_EYERAVFRAMEPRIVATE_HPP
#define EYERLIB_EYERAVFRAMEPRIVATE_HPP

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVFramePrivate
    {
    public:
        AVFrame * frame = nullptr;
        double secPTS = 0.0;

        std::vector<uint8_t *> data;
    };
}

#endif //EYERLIB_EYERAVFRAMEPRIVATE_HPP
