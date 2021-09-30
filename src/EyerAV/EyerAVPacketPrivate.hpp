#ifndef EYERLIB_EYERAVPACKETPRIVATE_HPP
#define EYERLIB_EYERAVPACKETPRIVATE_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    class EyerAVPacketPrivate
    {
    public:
        AVPacket * packet = nullptr;
    };
}

#endif //EYERLIB_EYERAVPACKETPRIVATE_HPP
