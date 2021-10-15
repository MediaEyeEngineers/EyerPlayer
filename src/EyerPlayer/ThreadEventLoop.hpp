#ifndef EYERCAMERA_THREADEVENTLOOP_HPP
#define EYERCAMERA_THREADEVENTLOOP_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerEvent/EyerEventHeader.hpp"
#include "ThreadReader.hpp"
#include "ThreadPlayCtr.hpp"
#include "QueueBox.hpp"

namespace Eyer
{
    class ThreadEventLoop : public EyerThread
    {
    public:
        ThreadEventLoop();
        ~ThreadEventLoop();

        int PushEvent(const EyerSmartPtr<Event> & event);

        virtual void Run() override;

        virtual int SetStopFlag() override;

    private:
        int ProcessEvent(const EyerSmartPtr<Event> & event);

        std::mutex mtx;
        std::condition_variable cv;
        EyerObserverQueue<EyerSmartPtr<Event>> eventQueue;

        QueueBox queueBox;

        // 线程
        ThreadPlayCtr * playCtrThread = nullptr;
        ThreadReader * readerThread = nullptr;
    };
}



#endif //EYERCAMERA_THREADEVENTLOOP_HPP
