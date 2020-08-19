#include "EyerPlayerEventManager.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerPlayerConstant.hpp"
#include "PlayerEvent.hpp"

namespace Eyer
{
    EyerPlayerEventManager::EyerPlayerEventManager()
    {
        eventQueue = new Eyer::EyerEventQueue();

        playerManager = new EyerPlayerThreadManager();
    }

    EyerPlayerEventManager::~EyerPlayerEventManager()
    {
        if(playerManager != nullptr){
            delete playerManager;
            playerManager = nullptr;
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

                playerManager->Open(openRequest->url, openRequest->GetRequestId(), eventQueue);
                playerManager->Play();
            }



            else if(event->GetType() == EventType::OPENResponse){
                EventOpenResponse * openResponse = (EventOpenResponse *)event;
                EyerLog("EventOpenResponse\n");
                if(openResponse->status == EventOpenStatus::OPEN_STATUS_SUCCESS){
                    EyerLog("EventOpenResponse OPEN_STATUS_SUCCESS\n");
                    MediaInfo mediaInfo = openResponse->mediaInfo;
                    mediaInfo.Print();
                }
                else if(openResponse->status == EventOpenStatus::OPEN_STATUS_FAIL){
                    EyerLog("EventOpenResponse OPEN_STATUS_FAIL\n");
                }
                else if(openResponse->status == EventOpenStatus::OPEN_STATUS_BUSY){
                    EyerLog("EventOpenResponse OPEN_STATUS_BUSY\n");
                }
                else{
                    EyerLog("EventOpenResponse UNKNOW\n");
                }
            }

            if(event != nullptr){
                delete event;
            }
        }

        // 结束之前回收所有的资源
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

    int EyerPlayerEventManager::SetGLCtx(Eyer::EyerGLContextThread * glCtx)
    {
        return playerManager->SetGLCtx(glCtx);
    }
    int EyerPlayerEventManager::UnbindGLCtx()
    {
        return playerManager->UnbindGLCtx();
    }
}