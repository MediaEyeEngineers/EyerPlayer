#ifndef EYERPLAYERLIB_THREAD_H
#define EYERPLAYERLIB_THREAD_H

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerAV/EyerAVQueue.hpp"

namespace EyerPlayer {
    class AVReaderThread;

    class AVReaderThread : public Eyer::EyerThread
    {
    public:
        AVReaderThread(Eyer::EyerString url, long long openEventId, Eyer::EyerEventQueue * eventQueue);
        ~AVReaderThread();
        virtual void Run();

    private:
        Eyer::EyerString url;
        long long openEventId = -1;
        Eyer::EyerEventQueue * eventQueue = nullptr;
    };
}

#endif // EYERPLAYERLIB_THREAD_H
