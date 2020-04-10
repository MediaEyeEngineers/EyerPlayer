#ifndef	EYER_LIB_EYER_THREAD_H
#define	EYER_LIB_EYER_THREAD_H

#include <thread>
#include <mutex>
#include <atomic>

namespace Eyer
{
    class EyerThread
    {
    public:
        EyerThread();
        ~EyerThread();

        virtual void Run() = 0;

        int Stop(int t = 1000);

        int WaitForStop(int t = 1000);

        int IsRunning();
        void Detach();
        void Join();

    protected:
        void SetRunning();
        void SetStoping();

        std::atomic_int stopFlag {0};
        std::atomic_int isRun {0};
    };
}

#endif