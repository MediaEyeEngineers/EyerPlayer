#ifndef	EYER_LIB_EYER_THREAD_H
#define	EYER_LIB_EYER_THREAD_H

#include <thread>
#include <mutex>
#include <atomic>
#include <queue>

namespace Eyer
{
    class EyerThread;
    class EyerRunnable;

    class EyerThread
    {
    public:
        EyerThread();
        ~EyerThread();

        virtual void Run() = 0;

        int Stop(int t = 1000);

        int IsRunning();
        int Start();



        int PushEvent(EyerRunnable * event);

        int StartEventLoop();
        int StopEventLoop();

        int EventLoop();

    protected:
        void SetRunning();
        void SetStoping();

        std::atomic_int stopFlag {0};
        std::atomic_int isRun {0};

        std::mutex eventLoopMut;
        std::atomic_int eventLooping {0};

    private:
        std::thread * t = nullptr;
        std::queue<EyerRunnable *> eventQueue;
    };

    class EyerRunnable
    {
    public:
        virtual void Run() = 0;
    };
}

#endif