#ifndef	EYER_LIB_AV_STREAM_PRIVATE_H
#define	EYER_LIB_AV_STREAM_PRIVATE_H

#include "EyerAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace Eyer
{
    class EyerAVStreamPrivate
    {
    public:
        AVCodecContext * codec = nullptr;
        AVCodecParameters * codecpar = nullptr;
        EyerAVStreamType type = EyerAVStreamType::STREAM_TYPE_UNKNOW;
    };
}


#endif