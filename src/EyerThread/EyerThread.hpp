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

        virtual void Run() = 0;


        int PushEvent(EyerRunnable * runnable);

        int StartEventLoop();
        int StopEventLoop();

        int EventLoop();

        int Notify();

    protected:
        std::atomic_int stopFlag {0};

        std::condition_variable cv;
        std::mutex mut;

    private:
        std::thread * t = nullptr;

        std::vector<EyerRunnable *> eventQueue;
        std::atomic_bool eventLoopFlag {false};

        std::promise<void> * eventLoopPromise = nullptr;
    };

    class EyerRunnable
    {
    public:
        virtual void Run() = 0;

        std::promise<void> promise;
        std::atomic_bool isOK {false};
    };
}

#endif