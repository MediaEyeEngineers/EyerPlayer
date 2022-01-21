#include "EyerDeocderQueue.hpp"

namespace Eyer
{
    EyerDeocderQueue::EyerDeocderQueue(const EyerAVStream & _stream, EyerConditionVariableBox * _cvBox)
        : stream(_stream)
        , cvBox(_cvBox)
    {

    }

    EyerDeocderQueue::~EyerDeocderQueue()
    {

    }

    int EyerDeocderQueue::PutPacket(EyerAVPacket * packet)
    {
        packetQueue.Lock();
        packetQueue.Push(packet);
        packetQueueSize += packet->GetSize();
        if(packetQueueSize <= 0){
            packetQueueSize = 0;
        }
        packetQueue.Unlock();
        return 0;
    }

    EyerAVPacket * EyerDeocderQueue::GetPacket()
    {
        EyerAVPacket * packet = nullptr;

        packetQueue.Lock();
        if(packetQueue.Size() > 0){
            packet = packetQueue.FrontPop();
        }
        if(packet != nullptr){
            packetQueueSize -= packet->GetSize();
            if(packetQueueSize <= 0){
                packetQueueSize = 0;
            }
        }
        packetQueue.Unlock();

        return packet;
    }

    int EyerDeocderQueue::GetPacketCacheSize()
    {
        return packetQueueSize;
    }

    int EyerDeocderQueue::GetStreamId()
    {
        return stream.GetStreamId();
    }
}