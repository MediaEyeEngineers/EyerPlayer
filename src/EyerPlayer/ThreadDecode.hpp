#ifndef EYERCAMERA_THREADDECODE_HPP
#define EYERCAMERA_THREADDECODE_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class QueueBox;

    class ThreadDecode : public EyerThread
    {
    public:
        ThreadDecode(const Eyer::EyerAVStream & _stream, QueueBox * _queueBox);
        ~ThreadDecode();

        virtual void Run() override;

        int GetStreamId();

        int PutPacket(EyerAVPacket * packet);

        virtual int SetStopFlag() override;

    public:
        std::atomic_int packetCacheSize {0};

    private:
        Eyer::EyerAVStream stream;
        Eyer::EyerObserverQueue<EyerAVPacket *> packetQueue;

        QueueBox * queueBox = nullptr;
    };
}

#endif //EYERCAMERA_THREADDECODE_HPP
