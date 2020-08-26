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

        int         Init(EyerAVStream & stream, jobject surface);
        int         Uninit();

        int         dequeueInputBuffer(long long timeoutUs);
        int         putInputData(int index, unsigned char * data, int size);
        void        queueInputBuffer(int index, int offset, int size, long long presentationTimeUs, int flags);

        int         dequeueOutputBuffer(long long timeoutUs);
        long long   getOutTime();
        int         releaseOutputBuffer(int index, bool render);

        int         flush();

    private:
        jobject eyerMediaCodec = nullptr;
    };

    class EyerMediaCodec2
    {
    public:
        EyerMediaCodec2();
        ~EyerMediaCodec2();

        int Init(EyerAVStream & stream, jobject surface);
        int Uninit();

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