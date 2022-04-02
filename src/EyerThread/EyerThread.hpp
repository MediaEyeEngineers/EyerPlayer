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
        int ClearAllEvent();

        // 进入悬空状态
        int StartAndWaitEventLoop();
        // 进入循环状态
        int EnterEventLoop();
        // 退出循环状态，进入悬空状态
        int WaitForFinishEventLoop();
        // 退出悬空状态
        int QuitEventLoop();

        int StartEventLoop();
        int StopEventLoop();

        int EventLoop();

        virtual int SetStopFlag();
        virtual int SetStartEventLoopFlag();

    protected:
        std::atomic_int stopFlag {0};

        std::vector<EyerRunnable *> eventList;
        std::atomic_int eventLoopFlag {0};

<<<<<<< HEAD
        std::promise<void> * startAndWaitEventLoopPromise = nullptr;
        std::promise<void> * waitForStartEventLoopPromise = nullptr;
        std::promise<void> * waitForFinishEventLoopPromise = nullptr;
        std::promise<void> * stopAndWaitEventLoopPromise = nullptr;
        std::promise<void> * stopOkAndWaitEventLoopPromise = nullptr;
=======
        std::promise<void> * onStartedPromise = nullptr;
        std::promise<void> * onStopPromise = nullptr;
        std::promise<void> * onStopFinishPromise = nullptr;
>>>>>>> f9fc630cc716281f2013a5411e7628052060cdbb
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