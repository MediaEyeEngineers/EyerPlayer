#ifndef EYERCAMERA_THREADPLAYCTR_HPP
#define EYERCAMERA_THREADPLAYCTR_HPP

#include "EyerThread/EyerThread.hpp"
#include "QueueBox.hpp"
#include "DecoderBox.hpp"

namespace Eyer
{
    class ThreadEventLoop;

    class ThreadPlayCtr : public EyerThread
    {
    public:
        ThreadPlayCtr(DecoderBox * _decoderBox, ThreadEventLoop * _eventLoop);
        ~ThreadPlayCtr();

        virtual void Run() override;
        virtual int SetStopFlag() override;
        virtual int SetStartEventLoopFlag() override;
    private:
        ThreadEventLoop * eventLoop = nullptr;
        DecoderBox * decoderBox = nullptr;
    };
}

#endif //EYERCAMERA_THREADPLAYCTR_HPP
