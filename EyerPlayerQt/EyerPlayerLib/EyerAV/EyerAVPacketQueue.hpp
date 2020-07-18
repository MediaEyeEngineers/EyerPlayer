//
// Created by redknot on 2020/3/29.
//

#ifndef EYE_LIB_EYERAVPACKETQUEUE_HPP
#define EYE_LIB_EYERAVPACKETQUEUE_HPP

#include <queue>
#include <mutex>
#include "EyerAV.hpp"

namespace Eyer
{
    class EyerAVPacketQueue {
    public:
        EyerAVPacketQueue();
        ~EyerAVPacketQueue();

        int Push(EyerAVPacket * pkt);
        int Front(EyerAVPacket * * pkt);
        int FrontPop(EyerAVPacket * * pkt);
    private:
        std::queue<EyerAVPacket *> packetQueue;
        std::mutex packetQueueMut;
    };
}

#endif //EYE_LIB_EYERAVPACKETQUEUE_HPP
