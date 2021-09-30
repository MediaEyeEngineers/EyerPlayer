#include "ThreadPlayCtr.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    void ThreadPlayCtr::Run()
    {
        EyerLog("ThreadPlayCtr Start\n");
        // 该线程用于控制视频流
        while(!stopFlag) {

        }
        EyerLog("ThreadPlayCtr End\n");
    }
}