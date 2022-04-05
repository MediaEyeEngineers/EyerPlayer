#ifndef EYERPLAYER_EYERDECODEQUEUEFFMPEG_HPP
#define EYERPLAYER_EYERDECODEQUEUEFFMPEG_HPP

#include "EyerThread/EyerThread.hpp"

#include "EyerDecodeQueueBase.hpp"

namespace Eyer
{
    class EyerDecodeQueueFFmpeg :
            public EyerDecodeQueueBase,
            public EyerThread
    {
    public:
        EyerDecodeQueueFFmpeg(const EyerAVStream & avStream);
        ~EyerDecodeQueueFFmpeg();

        virtual int StartDecoder() override;
        virtual int StopDeocder() override;

        virtual void Run() override;
    };
}

#endif //EYERPLAYER_EYERDECODEQUEUEFFMPEG_HPP
