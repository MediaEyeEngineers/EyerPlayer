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
        AVReaderThread(Eyer::EyerString url);
        ~AVReaderThread();
        virtual void Run();

    private:
        Eyer::EyerString url;
    };
}

#endif // EYERPLAYERLIB_THREAD_H
