#ifndef EYERCAMERA_THREADDECODE_HPP
#define EYERCAMERA_THREADDECODE_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class ThreadDecode : public EyerThread
    {
    public:
        ThreadDecode(const Eyer::EyerAVStream & stream, Eyer::EyerObserverQueue<EyerAVPacket *> * _packetQueue);
        ~ThreadDecode();

        virtual void Run() override;

    private:
        Eyer::EyerObserverQueue<EyerAVPacket *> * packetQueue = nullptr;
        Eyer::EyerAVStream stream;
    };
}

#endif //EYERCAMERA_THREADDECODE_HPP
