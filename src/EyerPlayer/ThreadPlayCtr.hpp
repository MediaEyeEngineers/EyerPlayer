#ifndef EYERCAMERA_THREADPLAYCTR_HPP
#define EYERCAMERA_THREADPLAYCTR_HPP

#include "EyerThread/EyerThread.hpp"
#include "QueueBox.hpp"
#include "DecoderBox.hpp"
#include "ThreadAndroidAudioPlay.hpp"

namespace Eyer
{
    class EventControlThread;

    class ThreadPlayCtr : public EyerThread
    {
    public:
        ThreadPlayCtr(DecoderBox * _decoderBox, EventControlThread * _eventLoop);
        ~ThreadPlayCtr();

        virtual void Run() override;
        virtual int SetStopFlag() override;
        virtual int SetStartEventLoopFlag() override;
    private:
        EventControlThread * eventLoop = nullptr;
        DecoderBox * decoderBox = nullptr;
    };
}

#endif //EYERCAMERA_THREADPLAYCTR_HPP
