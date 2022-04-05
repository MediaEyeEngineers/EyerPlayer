#ifndef EYERPLAYER_EYERDECODEQUEUEBASE_HPP
#define EYERPLAYER_EYERDECODEQUEUEBASE_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

namespace Eyer
{
    class EyerDecodeQueueBase
    {
    public:
        EyerDecodeQueueBase(const EyerAVStream & avStream);
        virtual ~EyerDecodeQueueBase();

        virtual int StartDecoder() = 0;
        virtual int StopDeocder() = 0;

        int GetCacheSize();
        int PutAVPacket(EyerAVPacket * packet);

    protected:
        std::atomic_int cacheSize {0};
        EyerObserverQueue<EyerAVPacket *> packetQueue;
        EyerAVStream avStream;
    };
}

#endif //EYERPLAYER_EYERDECODEQUEUEBASE_HPP
