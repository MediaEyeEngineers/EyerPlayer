#ifndef	EYER_LIB_AV_ENCODER_PRIVATE_H
#define	EYER_LIB_AV_ENCODER_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace Eyer
{
    class EyerAVEncoderPrivate
    {
    public:
        AVCodecContext * codecContext = nullptr;
    };
}

#endif