#include "EyerPlayerThreadManager.hpp"
#include "EyerPlayerConstant.hpp"
#include "PlayerEvent.hpp"

namespace EyerPlayer {
    EyerPlayerThreadManager::EyerPlayerThreadManager()
    {
        frameQueueManager = new AVFrameQueueManager();
    }

    EyerPlayerThreadManager::~EyerPlayerThreadManager()
    {
        if(frameQueueManager != nullptr){
            frameQueueManager->ClearAndDelete();
            delete frameQueueManager;
            frameQueueManager = nullptr;
        }
    }

    int EyerPlayerThreadManager::Open(Eyer::EyerString url, long long openEventId, Eyer::EyerEventQueue * eventQueue)
    {
        if(readerThread != nullptr){
            EventOpenResponse * openResponseEvent = new EventOpenResponse();
            openResponseEvent->SetFrom(EventTag::EVENT_MANAGER);
            openResponseEvent->SetTo(EventTag::EVENT_MANAGER);
            openResponseEvent->SetRequestId(openEventId);
            openResponseEvent->status = EventOpenStatus::OPEN_STATUS_BUSY;
            eventQueue->Push(openResponseEvent);

            return -1;
        }

        readerThread = new AVReaderThread(url, openEventId, eventQueue, frameQueueManager);
        readerThread->Start();

        return 0;
    }

    int EyerPlayerThreadManager::Play()
    {
        if(readerThread == nullptr){
            return -1;
        }

        if(playerCtr != nullptr){
            playerCtr->Stop();
            delete playerCtr;
            playerCtr = nullptr;
        }

        playerCtr = new PlayCtrThread(frameQueueManager);
        playerCtr->Start();

        return 0;
    }

    int EyerPlayerThreadManager::Pause()
    {
        return 0;
    }

    int EyerPlayerThreadManager::Stop()
    {
        if(readerThread != nullptr){
            readerThread->Stop();
            delete readerThread;
            readerThread = nullptr;
        }

        if(playerCtr != nullptr){
            playerCtr->Stop();
            delete playerCtr;
            playerCtr = nullptr;
        }

        return 0;
    }

    int EyerPlayerThreadManager::SetGLCtx(Eyer::EyerGLContextThread * glCtx)
    {
        if(playerCtr != nullptr){
            playerCtr->SetGLCtx(glCtx);
        }
        return 0;
    }
}