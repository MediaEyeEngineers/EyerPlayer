#ifndef EYERCAMERA_THREADEVENTLOOP_HPP
#define EYERCAMERA_THREADEVENTLOOP_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerEvent/EyerEventHeader.hpp"
#include "ThreadReader.hpp"
#include "ThreadPlayCtr.hpp"
#include "QueueBox.hpp"
#include "EyerPlayerContext.hpp"

namespace Eyer
{
    class EventControlThread : public EyerThread
    {
    public:
        EventControlThread();
        ~EventControlThread();

        int PushEvent(Event * event);

        virtual void Run() override;
        virtual int SetStopFlag() override;

    private:
        int ProcessEvent(Event * event);

        std::mutex mtx;
        std::condition_variable cv;
        EyerObserverQueue<Event *> eventQueue;

        EyerPlayerContext playerContext;
        ThreadReader * threadReader = nullptr;
    };
}

#endif //EYERCAMERA_THREADEVENTLOOP_HPP
