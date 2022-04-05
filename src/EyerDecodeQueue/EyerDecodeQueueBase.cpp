#include "EyerDecodeQueueBase.hpp"

namespace Eyer
{
    EyerDecodeQueueBase::EyerDecodeQueueBase(const EyerAVStream & _avStream)
        : avStream(_avStream)
    {

    }

    EyerDecodeQueueBase::~EyerDecodeQueueBase()
    {

    }

    int EyerDecodeQueueBase::GetCacheSize()
    {
        return cacheSize;
    }

    int EyerDecodeQueueBase::PutAVPacket(EyerAVPacket * packet)
    {
        packetQueue.Push(packet);
        cacheSize += packet->GetSize();
        return 0;
    }
}