#ifndef	EYER_LIB_EYER_THREAD_H
#define	EYER_LIB_EYER_THREAD_H

#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>
#include <future>

namespace Eyer
{
    class EyerThread;
    class EyerRunnable;

    class EyerThread
    {
    public:
        EyerThread();
        virtual ~EyerThread();

        int Start();
        int Stop();

        virtual int SetStopFlag();

        virtual void Run() = 0;


        int PushEvent(EyerRunnable * runnable);
        int ClearAllEvent();

        int StartEventLoop();
        virtual int SetStartEventLoopFlag();

        int StopEventLoop();

        int EventLoop();

    protected:
        std::atomic_int stopFlag {0};

        std::vector<EyerRunnable *> eventList;
        std::atomic_int eventLoopFlag {0};

        std::promise<void> * onStartedPromise = nullptr;
        std::promise<void> * onEventFinishPromise = nullptr;
        std::promise<void> * onStopedPromise = nullptr;
    private:
        std::thread * t = nullptr;
    };

    class EyerRunnable
    {
    public:
        virtual void Run() = 0;
    };
}

#endif