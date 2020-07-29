#include "EyerPlayerEventManager.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerPlayerConstant.hpp"
#include "PlayerEvent.hpp"

namespace EyerPlayer
{
    EyerPlayerEventManager::EyerPlayerEventManager()
    {
        eventQueue = new Eyer::EyerEventQueue();
    }

    EyerPlayerEventManager::~EyerPlayerEventManager()
    {
        if(readerThread != nullptr){
            readerThread->Stop();
            delete readerThread;
            readerThread = nullptr;
        }

        if(eventQueue != nullptr){
            delete eventQueue;
            eventQueue = nullptr;
        }
    }

    void EyerPlayerEventManager::Run()
    {
        EyerLog("Event Manager Start\n");
        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            Eyer::EyerEvent * event = nullptr;
            eventQueue->FrontTargetAndPop(event, EventTag::EVENT_MANAGER);
            if(event == nullptr){
                continue;
            }

            if(event->GetType() == EventType::OPENRequest){
                EventOpenRequest * openRequest = (EventOpenRequest *)event;
                EyerLog("OPENRequest\n");
                EyerLog("Url: %s\n", openRequest->url.str);
                
                if(readerThread != nullptr){
                    //TODO 返回错误
                }
                else{
                    readerThread = new AVReaderThread(openRequest->url, openRequest->GetRequestId(), eventQueue);
                    readerThread->Start();
                }
            }

            if(event != nullptr){
                delete event;
            }
        }

        // 结束之前回收所有的资源
        if(readerThread != nullptr){
            readerThread->Stop();
            delete readerThread;
            readerThread = nullptr;
        }
        EyerLog("Event Manager End\n");
    };

    int EyerPlayerEventManager::PushEvent(Eyer::EyerEvent * event)
    {
        return eventQueue->Push(event);
    }

    long long EyerPlayerEventManager::GenId()
    {
        return eventQueue->GetEventId();
    }
}