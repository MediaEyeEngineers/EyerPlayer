#ifndef EYERPLAYER_EYERDEOCDEQUEUE_HPP
#define EYERPLAYER_EYERDEOCDEQUEUE_HPP

#include "EyerAV/EyerAV.hpp"
#include "EyerThread/EyerThreadHeader.hpp"

namespace Eyer
{
    class EyerDeocdeQueue : public EyerThread
    {
    public:
        EyerDeocdeQueue(const EyerAVStream & _stream, EyerConditionVariableBox * _cvBox);
        virtual ~EyerDeocdeQueue();

        virtual int StartDecode() = 0;
        virtual int StopDecode() = 0;

        int PutPacket(EyerAVPacket * packet);
        int GetPacketCacheSize();

        int GetFrameSize();

        int GetStreamId();

    protected:
        EyerAVStream stream;
        EyerConditionVariableBox * cvBox = nullptr;

        std::atomic<int> packetQueueSize {0};
        Eyer::EyerObserverQueue<EyerAVPacket *> packetQueue;
        Eyer::EyerObserverQueue<EyerAVFrame *> frameQueue;
    };
}



#endif //EYERPLAYER_EYERDEOCDEQUEUE_HPP
