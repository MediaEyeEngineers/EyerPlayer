#include "IOReadThread.hpp"

namespace Eyer
{
    IOReadThread::IOReadThread(EyerPlayerContext * _playerContext)
        : playerContext(_playerContext)
    {

    }

    IOReadThread::~IOReadThread()
    {

    }

    void IOReadThread::Run()
    {
        EyerLog("IOReadThread Start\n");
        EyerLog("URL: %s\n", playerContext->url.c_str());



        while(1){
            if(stopFlag){
                break;
            }
        }
        EyerLog("IOReadThread End\n");
    }
}