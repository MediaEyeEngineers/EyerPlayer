#include "ThreadReader.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    void ThreadReader::Run()
    {
        EyerLog("ThreadReader Start\n");
        // 该线程用于读取视频流
        while(!stopFlag) {

        }
        EyerLog("ThreadReader End\n");
    }
}