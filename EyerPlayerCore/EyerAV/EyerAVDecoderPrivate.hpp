#ifndef	EYER_LIB_AV_DECODER_PRIVATE_H
#define	EYER_LIB_AV_DECODER_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
}

namespace Eyer
{
    class EyerAVDecoderPrivate
    {
    public:
        AVCodecContext * codecContext = nullptr;
        int isHW = 0;
    };
}

#endif