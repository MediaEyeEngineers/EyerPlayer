#ifndef EYERCAMERA_THREADREADER_HPP
#define EYERCAMERA_THREADREADER_HPP

#include "EyerThread/EyerThread.hpp"
#include "QueueBox.hpp"
#include "ThreadPlayCtr.hpp"

namespace Eyer
{
    class ThreadEventLoop;

    class ThreadReader : public EyerThread
    {
    public:
        ThreadReader(const EyerString & url, QueueBox * _queueBox, ThreadEventLoop * _eventLoop);
        ~ThreadReader();

        virtual void Run() override;

        virtual int SetStopFlag() override;
        virtual int SetStartEventLoopFlag() override;

        int Pause();
        int Resume();

    private:
        ThreadEventLoop * eventLoop = nullptr;
        QueueBox * queueBox = nullptr;
        EyerString url;

        ThreadPlayCtr * playCtr = nullptr;
    };
}

#endif //EYERCAMERA_THREADREADER_HPP
