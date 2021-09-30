#include "ThreadReader.hpp"

#include "EyerCore/EyerCore.hpp"
#include "ThreadDecode.hpp"

namespace Eyer
{
    void ThreadReader::Run()
    {
        EyerLog("ThreadReader Start\n");
        ThreadDecode decoder;
        decoder.Start();
        // 该线程用于读取视频流
        while(!stopFlag) {

        }
        decoder.Stop();
        EyerLog("ThreadReader End\n");
    }
}