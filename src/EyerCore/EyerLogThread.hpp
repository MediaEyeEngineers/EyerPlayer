#ifndef EYERLIB_EYERLOGTHREAD_HPP
#define EYERLIB_EYERLOGTHREAD_HPP

#include "EyerLogBean.hpp"
#include "EyerLockQueue.hpp"
#include "EyerThread/EyerThread.hpp"
#include "EyerLogParam.hpp"
#include "EyerObserverQueue.hpp"
#include "EyerObserver.hpp"

namespace Eyer
{
    class EyerLogThread : public EyerThread , public EyerObserver
    {
    public:
        class GarbageCollector {
        public:
            ~GarbageCollector() {
                if (EyerLogThread::instance != nullptr) {
                    EyerLogThread::instance->Stop();
                    delete EyerLogThread::instance;
                    EyerLogThread::instance = nullptr;
                }
            }
        };
        static GarbageCollector gc;

        static int eyer_log_thread_flag;

        static EyerLogThread * instance;
        static EyerLogThread * GetInstance();

        EyerLogThread();
        ~EyerLogThread();

        virtual void Run();

        virtual int Update();

        virtual int BeforeStop();

        int Clear();

        int SetLevel(int _level);

        int SetPath(const EyerString & path);

        int SetParam(EyerLogParam & param);

        int PutLog(EyerLogBean * logBean);

    private:
        EyerObserverQueue<EyerLogBean *> logQueue;
        int level = 5;

        int inline PrintLog(EyerLogBean * logBean);

        EyerLogParam param;
        EyerString path;

        std::condition_variable cv;
        std::mutex cvMtx;
    };
}



#endif //EYERLIB_EYERLOGTHREAD_HPP
