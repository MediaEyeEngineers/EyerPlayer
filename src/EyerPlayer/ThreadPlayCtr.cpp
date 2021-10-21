#include "ThreadPlayCtr.hpp"

#include "EyerCore/EyerCore.hpp"
#include "ThreadEventLoop.hpp"

namespace Eyer
{
    ThreadPlayCtr::ThreadPlayCtr(QueueBox * _queueBox, ThreadEventLoop * _eventLoop)
        : eventLoop(_eventLoop)
        , queueBox(_queueBox)
    {

    }

    ThreadPlayCtr::~ThreadPlayCtr()
    {

    }

    void ThreadPlayCtr::Run()
    {
        EyerLog("ThreadPlayCtr Start\n");
        // 该线程用于控制视频流
        while(!stopFlag) {
            std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
            while(!stopFlag) {
                queueBox->cvBox.cv.wait(locker);
            }


        }
        EyerLog("ThreadPlayCtr End\n");
    }

    int ThreadPlayCtr::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
        stopFlag = 1;
        queueBox->cvBox.cv.notify_all();
        return 0;
    }
}