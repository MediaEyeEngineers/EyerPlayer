#include "EyerPlayerEventManager.h"
#include "EyerPlayerConstant.h"
#include "PlayerEvent.hpp"

#include <QDebug>

namespace EyerPlayer {
    EyerPlayerEventManager::EyerPlayerEventManager(AVFrameQueueManager * _queueManager)
    {
        eventQueue = new Eyer::EyerEventQueue();
        queueManager = _queueManager;
    }

    EyerPlayerEventManager::~EyerPlayerEventManager()
    {
        if(readerThread != nullptr){
            readerThread->Stop();
            delete readerThread;
            readerThread = nullptr;
        }

        // 清空事件队列中来不及处理的事件
        if(eventQueue->Size() > 0){
            Eyer::EyerEvent * event = nullptr;
            eventQueue->Front(event);
            if(event != nullptr){
                delete event;
            }
        }

        if(eventQueue != nullptr){
            delete eventQueue;
            eventQueue = nullptr;
        }
    }

    void EyerPlayerEventManager::run()
    {
        isRun = 1;

        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            Eyer::EyerEvent * event = nullptr;
            eventQueue->FrontTargetAndPop(event, EventTag::EVENT_MANAGER);
            if(event != nullptr){
                if(event->GetType() == EventType::OPENRequest){
                    EventOpenRequest * openRequest = (EventOpenRequest *)event;
                    if(readerThread != nullptr){
                        EventOpenResponse * event = new EventOpenResponse();
                        event->SetFrom(EventTag::EVENT_MANAGER);
                        event->SetTo(EventTag::EVENT_MANAGER);
                        event->SetRequestId(openRequest->GetRequestId());
                        event->status = EventOpenStatus::OPEN_STATUS_BUSY;
                        eventQueue->Push(event);
                    }
                    else{
                        readerThread = new AVReaderThread(openRequest->url, eventQueue, openRequest->GetRequestId(), queueManager, 0.0);
                        readerThread->Start();
                    }
                }

                if(event->GetType() == EventType::STOPRequest){
                    EventStopRequest * stopRequest = (EventStopRequest *)event;
                    if(readerThread != nullptr){
                        readerThread->Stop();
                        delete readerThread;
                        readerThread = nullptr;

                        EventStopResponse * event = new EventStopResponse();
                        event->SetFrom(EventTag::EVENT_MANAGER);
                        event->SetTo(EventTag::EVENT_MANAGER);
                        event->SetRequestId(stopRequest->GetRequestId());
                        event->status = EventStopStatus::STOP_STATUS_SUCCESS;
                        eventQueue->Push(event);
                    }
                    else{
                        EventStopResponse * event = new EventStopResponse();
                        event->SetFrom(EventTag::EVENT_MANAGER);
                        event->SetTo(EventTag::EVENT_MANAGER);
                        event->SetRequestId(stopRequest->GetRequestId());
                        event->status = EventStopStatus::STOP_STATUS_NOT_OPEN;
                        eventQueue->Push(event);
                    }
                }

                if(event->GetType() == EventType::PLAYRequest){
                    EventPlayRequest * playRequest = (EventPlayRequest *)event;
                    if(readerThread != nullptr){
                        readerThread->Play();
                    }
                }

                if(event->GetType() == EventType::PAUSERequest){
                    EventPauseRequest * pauseRequest = (EventPauseRequest *)event;
                    if(readerThread != nullptr){
                        readerThread->Pause();
                    }
                }

                if(event->GetType() == EventType::SEEKRequest){
                    EventSeekRequest * seekRequest = (EventSeekRequest *)event;

                    Eyer::EyerString url;

                    if(readerThread != nullptr){
                        readerThread->Stop();

                        url = readerThread->GetURL();

                        delete readerThread;
                        readerThread = nullptr;
                    }

                    readerThread = new AVReaderThread(url, eventQueue, -1, queueManager, seekRequest->time);
                    readerThread->Start();
                }

                if(event->GetType() == EventType::UPDATEUIRequest){
                    EventUpdateUIRequest * updateUIRequest = (EventUpdateUIRequest *)event;
                    Eyer::EyerAVFrame * frame = updateUIRequest->frame;
                    emit onUpdateUI(updateUIRequest->streamId, frame);
                }

                if(event->GetType() == EventType::OPENResponse){
                    EventOpenResponse * openResponse = (EventOpenResponse *)event;
                    MediaInfo * info = new MediaInfo(openResponse->mediaInfo);
                    emit onOpen(openResponse->status, openResponse->GetRequestId(), info);
                }

                if(event->GetType() == EventType::STOPResponse){
                    EventStopResponse * stopResponse = (EventStopResponse *)event;
                    emit onStop(stopResponse->status, stopResponse->GetRequestId());
                }

                if(event->GetType() == EventType::PROGRESSRequest){
                    EventProgressRequest * progressEvent = (EventProgressRequest *)event;
                    emit onProgress(progressEvent->playTime);
                }

                if(event->GetType() == EventType::LAGStartRequest){
                    EventLagStartRequest * lagStartRequest = (EventLagStartRequest *)event;
                    emit onLagStart(lagStartRequest->GetId());
                }
                if(event->GetType() == EventType::LAGStopRequest){
                    EventLagStopRequest * lagStopRequest = (EventLagStopRequest *)event;
                    emit onLagStop(lagStopRequest->GetId());
                }

                delete event;
            }
        }

        stopFlag = 0;
        isRun = 0;
    }

    int EyerPlayerEventManager::Stop()
    {
        stopFlag = 1;
        while(isRun){
            Eyer::EyerTime::EyerSleep(1000);
        }
        return 0;
    }

    int EyerPlayerEventManager::PushEvent(Eyer::EyerEvent * event)
    {
        return eventQueue->Push(event);
    }

    long long EyerPlayerEventManager::GenId()
    {
        return eventQueue->GetEventId();
    }
}
