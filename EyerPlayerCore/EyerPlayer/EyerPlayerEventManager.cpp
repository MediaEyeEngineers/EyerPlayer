#include "EyerPlayerEventManager.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerPlayerConstant.hpp"
#include "PlayerEvent.hpp"

namespace Eyer
{
    EyerPlayerEventManager::EyerPlayerEventManager(AVFrameQueueManager * _frameQueueManager)
    {
        eventQueue = new Eyer::EyerEventQueue();
        playerManager = new EyerPlayerThreadManager(eventQueue, _frameQueueManager);
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

    int EyerPlayerEventManager::SetCallback(EyerPlayerCallback * _callback)
    {
        callback = _callback;
        return 0;
    }

    void EyerPlayerEventManager::Run()
    {
        EyerLog("Event Manager Start\n");

        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);

            Eyer::EyerEvent * event = nullptr;
            eventQueue->FrontTargetAndPop(event, EventTag::EVENT_MANAGER);
            if(event == nullptr){
                continue;
            }

            if(event->GetType() == EventType::OPENRequest){
                EventOpenRequest * openRequest = (EventOpenRequest *)event;
                EyerLog("OPENRequest\n");
                EyerLog("Url: %s\n", openRequest->url.str);

                playerManager->Open(openRequest->url, openRequest->playerConfig, openRequest->GetRequestId());
            }

            if(event->GetType() == EventType::PLAYRequest){
                EventPlayRequest * playRequest = (EventPlayRequest *)event;
                EyerLog("PlayRequest\n");

                playerManager->Play();
            }

            if(event->GetType() == EventType::PAUSERequest){
                EventPauseRequest * playRequest = (EventPauseRequest *)event;
                EyerLog("PauseRequest\n");

                playerManager->Pause();
            }

            if(event->GetType() == EventType::STOPRequest){
                EventStopRequest * stopRequest = (EventStopRequest *)event;
                EyerLog("StopRequest\n");

                playerManager->Stop();
            }

            if(event->GetType() == EventType::SEEKRequest){
                EventSeekRequest * seekRequest = (EventSeekRequest *)event;
                EyerLog("SeekRequest\n");

                playerManager->Seek(seekRequest->time);
            }

            if(event->GetType() == EventType::SwitchRepresentationRequest){
                EventSwitchRepresentationRequest * switchRepresentationRequest = (EventSwitchRepresentationRequest *)event;
                EyerLog("SwitchRepresentation\n");

                playerManager->SwitchRepresentation(1);
            }





            else if(event->GetType() == EventType::OPENResponse){
                EventOpenResponse * openResponse = (EventOpenResponse *)event;
                // EyerLog("EventOpenResponse\n");
                MediaInfo mediaInfo;
                if(openResponse->status == EventOpenStatus::OPEN_STATUS_SUCCESS){
                    EyerLog("EventOpenResponse OPEN_STATUS_SUCCESS\n");
                    mediaInfo.Print();
                    mediaInfo = openResponse->mediaInfo;
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
                if(callback != nullptr){
                    callback->OnOpen(openResponse->status, mediaInfo);
                }
            }
            else if(event->GetType() == EventType::PROGRESSRequest){
                EventProgressRequest * progressRequest = (EventProgressRequest *)event;
                // EyerLog("PROGRESSRequest: %f\n", progressRequest->progress);
                if(callback != nullptr){
                    callback->OnProgress(progressRequest->progress);
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

    int EyerPlayerEventManager::SetSurface(jobject surface)
    {
        return playerManager->SetSurface(surface);
    }
}