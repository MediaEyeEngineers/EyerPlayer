#ifndef EYERPLAYERANDROID_EYERDEOCDERQUEUEFFMPEG_HPP
#define EYERPLAYERANDROID_EYERDEOCDERQUEUEFFMPEG_HPP

#include "EyerDeocderQueue.hpp"
#include "EyerThread/EyerThreadHeader.hpp"

namespace Eyer
{
    class EyerDeocderQueueFFmpeg : public EyerDeocderQueue, public EyerThread
    {
    public:
        EyerDeocderQueueFFmpeg(const EyerAVStream & _stream, EyerConditionVariableBox * _cvBox);
        ~EyerDeocderQueueFFmpeg();

        virtual int StartDecode() override;
        virtual int StopDecode() override;
        virtual int FlushDecoder() override;

        virtual void Run() override;
        virtual int SetStopFlag() override;
        virtual int SetStartEventLoopFlag() override;
    };
}

#endif //EYERPLAYERANDROID_EYERDEOCDERQUEUEFFMPEG_HPP
