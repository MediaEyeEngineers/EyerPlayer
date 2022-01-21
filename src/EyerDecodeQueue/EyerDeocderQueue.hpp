#ifndef EYERPLAYERANDROID_EYERDEOCDERQUEUE_HPP
#define EYERPLAYERANDROID_EYERDEOCDERQUEUE_HPP

#include "EyerAV/EyerAV.hpp"
#include "EyerThread/EyerThreadHeader.hpp"

namespace Eyer
{
    class EyerDeocderQueue
    {
    public:
        EyerDeocderQueue(const EyerAVStream & _stream, EyerConditionVariableBox * _cvBox);
        ~EyerDeocderQueue();

        virtual int StartDecode() = 0;
        virtual int StopDecode() = 0;
        virtual int FlushDecoder() = 0;

        int GetStreamId();

        int PutPacket(EyerAVPacket * packet);
        int GetPacketCacheSize();

        EyerAVPacket * GetPacket();

    protected:
        EyerAVStream stream;
        EyerConditionVariableBox * cvBox = nullptr;

        std::atomic<int> packetQueueSize {0};
        Eyer::EyerObserverQueue<EyerAVPacket *> packetQueue;
    };
}

#endif //EYERPLAYERANDROID_EYERDEOCDERQUEUE_HPP
