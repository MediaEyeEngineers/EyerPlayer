#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerPlayerLib.h"
#include "PlayerEvent.hpp"
#include <QDebug>

namespace EyerPlayer {
    EventManagerThread::EventManagerThread()
    {
        eventQueue = new Eyer::EyerEventQueue();
    }

    EventManagerThread::~EventManagerThread()
    {
        if(eventQueue != nullptr){
            delete eventQueue;
            eventQueue = nullptr;
        }
    }

    void EventManagerThread::Run()
    {
        SetRunning();

        while(!stopFlag){
            {
                Eyer::EyerEvent * event = nullptr;
                eventQueue->FrontTargetAndPop(event, EventTag::EVENT_MANAGER);

                if(event == nullptr){
                    continue;
                }

                if(event->GetType() == EventType::OPENRequest){
                    EventOpenRequest * openEvent = (EventOpenRequest *)event;
                    qDebug() << "Client Call Open : " << openEvent->url.str << endl;
                }

                delete event;
            }


            {
                Eyer::EyerEvent * event = nullptr;
                eventQueue->FrontTargetAndPop(event, EventTag::PLAYER);

                if(event == nullptr){
                    continue;
                }

                delete event;
            }

            Eyer::EyerTime::EyerSleep(1000 * 5);
        }

        SetStoping();
    }
}
