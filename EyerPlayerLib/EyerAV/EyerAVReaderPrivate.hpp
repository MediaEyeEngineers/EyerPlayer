#ifndef	EYER_LIB_AV_READER_PRIVATE_H
#define	EYER_LIB_AV_READER_PRIVATE_H

#include "EyerAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace Eyer
{
    class EyerAVReaderPrivate
    {
    public:
        EyerString path;
        AVFormatContext * formatCtx = nullptr;
    };
}

#endif