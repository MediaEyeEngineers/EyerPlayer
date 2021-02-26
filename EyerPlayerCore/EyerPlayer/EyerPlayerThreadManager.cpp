#include "EyerPlayerThreadManager.hpp"
#include "EyerPlayerConstant.hpp"
#include "PlayerEvent.hpp"

namespace Eyer {
    EyerPlayerThreadManager::EyerPlayerThreadManager(Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _frameQueueManager)
    {
        eventQueue = _eventQueue;
        frameQueueManager = _frameQueueManager;
    }

    EyerPlayerThreadManager::~EyerPlayerThreadManager()
    {
        Stop();
    }

    int EyerPlayerThreadManager::Open(Eyer::EyerString url, const EyerPlayerConfig & _playerConfig, long long openEventId)
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

        playerConfig = _playerConfig;

        frameQueueManager->ClearAndDelete();

        readerThread = new AVReaderThread(url, playerConfig, openEventId, eventQueue, frameQueueManager);
        readerThread->SetSurface(surface);
        readerThread->Start();

        return 0;
    }

    int EyerPlayerThreadManager::Play()
    {
        if(readerThread == nullptr){
            return -1;
        }

        if(readerThread->GetAVReaderStatus() != AVReaderStatus::READER_STATUS_OPEN_SUCCESS){
            return -2;
        }

        MediaInfo mediaInfo;
        readerThread->GetMediaInfo(mediaInfo);

        if(playerCtr == nullptr){
            playerCtr = new AVPlayCtrThread(playerConfig, frameQueueManager, eventQueue, mediaInfo, videoTime);

            glCtxMut.lock();
            playerCtr->SetGLCtx(glCtx);
            glCtxMut.unlock();

            playerCtr->Start();
        }

        PLAY_PlayCtr_Runnable playCtrRunnable(playerCtr);
        playerCtr->PushEvent(&playCtrRunnable);
        playerCtr->StartEventLoop();
        playerCtr->StopEventLoop();

        return 0;
    }

    int EyerPlayerThreadManager::Pause()
    {
        if(playerCtr == nullptr){
            return -1;
        }

        PAUSE_PlayCtr_Runnable pauseCtrRunnable(playerCtr);
        playerCtr->PushEvent(&pauseCtrRunnable);
        playerCtr->StartEventLoop();
        playerCtr->StopEventLoop();

        return 0;
    }

    int EyerPlayerThreadManager::Stop()
    {
        if(playerCtr != nullptr){
            playerCtr->Stop();
            delete playerCtr;
            playerCtr = nullptr;
        }

        if(readerThread != nullptr){
            readerThread->Stop();
            delete readerThread;
            readerThread = nullptr;
        }

        frameQueueManager->ClearAndDelete();
        frameQueueManager->GetMediaCodecQueueUninit();

        videoTime = 0.0;

        return 0;
    }

    int EyerPlayerThreadManager::Seek(double time)
    {
        if(readerThread == nullptr){
            return -1;
        }

        if(playerCtr != nullptr){
            SEEK_PlayCtr_Runnable seekPlayCtrRunnable(playerCtr, time);
            playerCtr->PushEvent(&seekPlayCtrRunnable);
            playerCtr->StartEventLoop();

            SEEK_Reader_Runnable seekReaderRunnable(readerThread, time);
            readerThread->PushEvent(&seekReaderRunnable);
            readerThread->StartEventLoop();
            readerThread->StopEventLoop();

            playerCtr->StopEventLoop();
        }

        return 0;
    }

    int EyerPlayerThreadManager::SwitchRepresentation(int representation)
    {
        if(readerThread == nullptr){
            return -1;
        }

        SWITCH_Representation_Runnable representationRunnable(readerThread, representation);
        readerThread->PushEvent(&representationRunnable);
        readerThread->StartEventLoop();
        readerThread->StopEventLoop();

        return 0;
    }

    int EyerPlayerThreadManager::SetGLCtx(Eyer::EyerGLContextThread * _glCtx)
    {
        glCtxMut.lock();
        glCtx = _glCtx;
        if(playerCtr != nullptr){
            playerCtr->SetGLCtx(glCtx);
        }
        glCtxMut.unlock();

        return 0;
    }

    int EyerPlayerThreadManager::UnbindGLCtx()
    {
        glCtxMut.lock();
        glCtx = nullptr;
        if(playerCtr != nullptr){
            playerCtr->SetGLCtx(glCtx);
        }
        glCtxMut.unlock();

        return 0;
    }

    int EyerPlayerThreadManager::SetSurface(jobject _surface)
    {
        surface = _surface;
        if(readerThread != nullptr){
            readerThread->SetSurface(surface);
        }

        return 0;
    }
}