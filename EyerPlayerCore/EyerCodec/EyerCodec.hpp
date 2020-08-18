#ifndef	EYER_CODEC_H
#define	EYER_CODEC_H

#include "EyerAV/EyerAV.hpp"
#include "EyerJNI/EyerJNIEnvManager.h"
#include <jni.h>

namespace Eyer
{
    class EyerMediaCodec
    {
    public:
        EyerMediaCodec();
        ~EyerMediaCodec();

        int Init(EyerAVStream & stream);

        int BindDecoderThread();
        int BindPlayCtrThread();

        int SendPacket(Eyer::EyerAVPacket *pkt );
        int RecvFrameRender();

    private:
        jobject eyerMediaCodec = nullptr;

        std::mutex mut;
    };
}

#endif