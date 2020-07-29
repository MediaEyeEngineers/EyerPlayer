//
// Created by redknot on 2020/3/29.
//

#include "EyerAVPacketQueue.hpp"
#include "EyerAVAV.hpp"

namespace Eyer
{
    EyerAVPacketQueue::EyerAVPacketQueue()
    {

    }

    EyerAVPacketQueue::~EyerAVPacketQueue()
    {
        packetQueueMut.lock();

        if(packetQueue.size() > 0) {
            EyerAVPacket * pkt = packetQueue.front();
            delete pkt;
            packetQueue.pop();
        }

        packetQueueMut.unlock();
    }

    int EyerAVPacketQueue::Push(EyerAVPacket * pkt)
    {
        packetQueueMut.lock();

        packetQueue.push(pkt);

        packetQueueMut.unlock();
        return 0;
    }

    int EyerAVPacketQueue::Front(EyerAVPacket * * pkt)
    {
        packetQueueMut.lock();

        *pkt = packetQueue.front();

        packetQueueMut.unlock();
        return 0;
    }

    int EyerAVPacketQueue::FrontPop(EyerAVPacket * * pkt)
    {
        packetQueueMut.lock();

        *pkt = packetQueue.front();
        packetQueue.pop();

        packetQueueMut.unlock();
        return 0;
    }
}