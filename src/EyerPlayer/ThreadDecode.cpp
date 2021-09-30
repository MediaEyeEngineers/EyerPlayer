#include "ThreadDecode.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    void ThreadDecode::Run()
    {
        EyerLog("ThreadDecode Start\n");
        // 该线程用于解码
        while(!stopFlag) {

        }

        EyerLog("ThreadDecode End\n");
    }
}