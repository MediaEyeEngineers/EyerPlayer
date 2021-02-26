#ifndef EYERPLAYERLIB_THREAD_MANAGER_H
#define EYERPLAYERLIB_THREAD_MANAGER_H

#include "EyerPlayerThread.hpp"
#include "EyerPlayer.hpp"

namespace Eyer {
    class EyerPlayerThreadManager{
    public:
        EyerPlayerThreadManager(Eyer::EyerEventQueue * eventQueue, AVFrameQueueManager * _frameQueueManager);
        ~EyerPlayerThreadManager();

        int Open(Eyer::EyerString url, const EyerPlayerConfig & playerConfig, long long openEventId);
        int Play();
        int Pause();
        int Stop();
        int Seek(double time);
        int SwitchRepresentation(int representation);

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

        EyerPlayerConfig playerConfig;

        double videoTime = 0.0;
    };
}

#endif // EYERPLAYERLIB_THREAD_MANAGER_H