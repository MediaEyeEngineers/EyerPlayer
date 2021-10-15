#include "ThreadPlayCtr.hpp"

#include "EyerCore/EyerCore.hpp"
#include "ThreadEventLoop.hpp"

namespace Eyer
{
    ThreadPlayCtr::ThreadPlayCtr(QueueBox * _queueBox, ThreadEventLoop * _eventLoop)
        : eventLoop(_eventLoop)
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

        }
        EyerLog("ThreadPlayCtr End\n");
    }
}