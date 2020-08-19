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

        int SendPacket(Eyer::EyerAVPacket * pkt);
        int RecvFrameRender();

        int DequeueOutputBuffer();
        long GetOutTime();
        int RenderFrame(int outindex);

    private:
        jobject eyerMediaCodec = nullptr;
    };
}

#endif