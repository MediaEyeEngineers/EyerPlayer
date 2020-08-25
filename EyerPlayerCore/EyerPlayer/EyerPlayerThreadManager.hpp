#ifndef EYERPLAYERLIB_THREAD_MANAGER_H
#define EYERPLAYERLIB_THREAD_MANAGER_H

#include "EyerPlayerThread.hpp"

namespace Eyer {
    class EyerPlayerThreadManager{
    public:
        EyerPlayerThreadManager(Eyer::EyerEventQueue * eventQueue);
        ~EyerPlayerThreadManager();

        int Open(Eyer::EyerString url, long long openEventId);
        int Play();
        int Pause();
        int Stop();

        int SetGLCtx(Eyer::EyerGLContextThread * glCtx);
        int UnbindGLCtx();

        int SetSurface(jobject _surface);

    private:
        Eyer::EyerEventQueue * eventQueue = nullptr;
        AVFrameQueueManager * frameQueueManager = nullptr;

        AVReaderThread * readerThread = nullptr;
        AVPlayCtrThread * playerCtr = nullptr;

        std::mutex glCtxMut;
        Eyer::EyerGLContextThread * glCtx = nullptr;
        jobject surface = nullptr;

        double videoTime = 0.0;
    };
}

#endif // EYERPLAYERLIB_THREAD_MANAGER_H