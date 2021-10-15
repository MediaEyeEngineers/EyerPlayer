#ifndef EYERCAMERA_THREADREADER_HPP
#define EYERCAMERA_THREADREADER_HPP

#include "EyerThread/EyerThread.hpp"
#include "QueueBox.hpp"

namespace Eyer
{
    class ThreadEventLoop;

    class ThreadReader : public EyerThread
    {
    public:
        ThreadReader(QueueBox * _queueBox, ThreadEventLoop * _eventLoop);
        ~ThreadReader();

        virtual void Run() override;

        virtual int SetStopFlag() override;

    private:
        ThreadEventLoop * eventLoop = nullptr;
        QueueBox * queueBox = nullptr;
    };
}

#endif //EYERCAMERA_THREADREADER_HPP
