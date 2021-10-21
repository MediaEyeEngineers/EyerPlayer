#include "EyerDeocdeQueue.hpp"

namespace Eyer
{
    EyerDeocdeQueue::EyerDeocdeQueue(const EyerAVStream & _stream, EyerConditionVariableBox * _cvBox)
        : stream(_stream)
        , cvBox(_cvBox)
    {

    }

    EyerDeocdeQueue::~EyerDeocdeQueue()
    {

    }

    int EyerDeocdeQueue::PutPacket(EyerAVPacket * packet)
    {
        packetQueue.Lock();
        packetQueue.Push(packet);
        packetQueueSize += packet->GetSize();
        packetQueue.Unlock();
        return 0;
    }

    int EyerDeocdeQueue::GetPacketCacheSize()
    {
        return packetQueueSize;
    }

    int EyerDeocdeQueue::GetStreamId()
    {
        return stream.GetStreamId();
    }

    int EyerDeocdeQueue::GetFrameSize()
    {
        return frameQueue.SizeLock();
    }
}