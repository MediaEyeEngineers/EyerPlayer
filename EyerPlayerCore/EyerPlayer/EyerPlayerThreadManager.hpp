#ifndef EYERPLAYERLIB_THREAD_MANAGER_H
#define EYERPLAYERLIB_THREAD_MANAGER_H

#include "EyerPlayerThread.hpp"

namespace Eyer {
    class EyerPlayerThreadManager{
    public:
        EyerPlayerThreadManager();
        ~EyerPlayerThreadManager();

        int Open(Eyer::EyerString url, long long openEventId, Eyer::EyerEventQueue * eventQueue);
        int Play();
        int Pause();
        int Stop();

        int SetGLCtx(Eyer::EyerGLContextThread * glCtx);
        int UnbindGLCtx();

        int SetSurface(jobject _surface);

    private:
        AVFrameQueueManager * frameQueueManager = nullptr;

        AVReaderThread * readerThread = nullptr;
        AVPlayCtrThread * playerCtr = nullptr;

        std::mutex glCtxMut;
        Eyer::EyerGLContextThread * glCtx = nullptr;
        jobject surface = nullptr;
    };
}

#endif // EYERPLAYERLIB_THREAD_MANAGER_H