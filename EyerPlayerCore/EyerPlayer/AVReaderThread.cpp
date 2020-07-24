#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"

namespace EyerPlayer {
    AVReaderThread::AVReaderThread(Eyer::EyerString _url)
    {
        url = _url;
    }

    AVReaderThread::~AVReaderThread()
    {

    }

    void AVReaderThread::Run()
    {
        EyerLog("AVReader Thread Start\n");
        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);
            Eyer::EyerAVReader reader(url);
            int ret = reader.Open();
        }
        EyerLog("AVReader Thread Start\n");
    }
}
