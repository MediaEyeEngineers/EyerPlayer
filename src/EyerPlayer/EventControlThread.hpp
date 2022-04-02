#ifndef EYERCAMERA_THREADEVENTLOOP_HPP
#define EYERCAMERA_THREADEVENTLOOP_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerEvent/EyerEventHeader.hpp"

#include "EyerPlayerContext.hpp"
#include "IOReadThread.hpp"

namespace Eyer
{
    class EventControlThread : public EyerThread
    {
    public:
        EventControlThread();
        ~EventControlThread();

        int PushEvent(EyerPlayerEvent * event);

        virtual void Run() override;
        virtual int SetStopFlag() override;

    private:
        int ProcessEvent(EyerPlayerEvent * event);

        std::mutex mtx;
        std::condition_variable cv;
        EyerObserverQueue<EyerPlayerEvent *> eventQueue;

        EyerPlayerContext playerContext;

        IOReadThread * ioReadThread = nullptr;
    };
}

#endif //EYERCAMERA_THREADEVENTLOOP_HPP
