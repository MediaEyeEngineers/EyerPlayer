#ifndef EYERPLAYERLIB_THREAD_MANAGER_H
#define EYERPLAYERLIB_THREAD_MANAGER_H

#include "EyerPlayerThread.hpp"

namespace EyerPlayer {
    class EyerPlayerThreadManager{
    public:
        EyerPlayerThreadManager();
        ~EyerPlayerThreadManager();

        int Open(Eyer::EyerString url, long long openEventId, Eyer::EyerEventQueue * eventQueue);
        int Play();
        int Pause();
        int Stop();

        int SetGLCtx(Eyer::EyerGLContextThread * glCtx);

    private:
        AVFrameQueueManager * frameQueueManager = nullptr;

        AVReaderThread * readerThread = nullptr;
        PlayCtrThread * playerCtr = nullptr;

        Eyer::EyerGLContextThread * glCtx = nullptr;
    };
}

#endif // EYERPLAYERLIB_THREAD_MANAGER_H