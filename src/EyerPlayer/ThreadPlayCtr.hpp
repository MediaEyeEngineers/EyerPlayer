#ifndef EYERCAMERA_THREADPLAYCTR_HPP
#define EYERCAMERA_THREADPLAYCTR_HPP

#include "EyerThread/EyerThread.hpp"
#include "QueueBox.hpp"

namespace Eyer
{
    class ThreadEventLoop;

    class ThreadPlayCtr : public EyerThread
    {
    public:
        ThreadPlayCtr(QueueBox * _queueBox, ThreadEventLoop * _eventLoop);
        ~ThreadPlayCtr();

        virtual void Run() override;
        virtual int SetStopFlag() override;
    private:
        ThreadEventLoop * eventLoop = nullptr;
        QueueBox * queueBox = nullptr;
    };
}

#endif //EYERCAMERA_THREADPLAYCTR_HPP
