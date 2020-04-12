#include "EyerPlayerThread.hpp"
#include "PlayerEvent.hpp"

#include <QDebug>

namespace EyerPlayer {
    PlayCtrThread::PlayCtrThread(Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _queueManager, int _recommendVideoIndex, int _recommendAudioIndex, double seekTime)
    {
        recommendVideoIndex = _recommendVideoIndex;
        recommendAudioIndex = _recommendAudioIndex;
        eventQueue = _eventQueue;
        queueManager = _queueManager;

        startPlayerPts = seekTime;
    }

    PlayCtrThread::~PlayCtrThread()
    {
        // TODO 回收所有的缓冲帧
    }

    void PlayCtrThread::Run()
    {
        SetRunning();

        // qDebug() << "Player THREAD Start" << endl;


        long long startTime = Eyer::EyerTime::GetTime();

        double lastUpdateProgressTime = 0.0;

        AVFrameQueue * videoQueue = nullptr;
        AVFrameQueue * audioQueue1 = nullptr;

        {
            Eyer::EyerString queueKey = Eyer::EyerString(EventTag::FRAME_QUEUE_DECODER_VIDEO) + Eyer::EyerString::Number(recommendVideoIndex);
            queueManager->GetQueue(queueKey, &videoQueue);
            if(videoQueue == nullptr){
                qDebug() << "Decoder Thread Get Frame Queue Fail" << endl;
            }
        }

        {
            Eyer::EyerString queueKey = Eyer::EyerString(EventTag::FRAME_QUEUE_DECODER_VIDEO) + Eyer::EyerString::Number(recommendAudioIndex);
            queueManager->GetQueue(queueKey, &audioQueue1);
            if(audioQueue1 == nullptr){
                qDebug() << "Decoder Thread Get Frame Queue Fail" << endl;
            }
        }


        AVFrameQueue * playerAudioFrameQueue = nullptr;
        queueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_AUDIO, &playerAudioFrameQueue);

        AVFrameQueue * playerVideoFrameQueue = nullptr;
        queueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_VIDEO, &playerVideoFrameQueue);

        Eyer::EyerAVFrame * videoFrame = nullptr;
        Eyer::EyerAVFrame * audioFrame = nullptr;

        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            long long nowTime = Eyer::EyerTime::GetTime();
            double dTime = (nowTime - startTime) / 1000.0;
            playerProgressPts = startPlayerPts + dTime;

            if(videoFrame == nullptr){
                videoQueue->FrontPop(&videoFrame);
            }


            if(lastUpdateProgressTime <= 0.0){
                EventProgressRequest * progressEvent = new EventProgressRequest();
                progressEvent->SetFrom(EventTag::EVENT_PLAYER_CTR);
                progressEvent->SetTo(EventTag::EVENT_MANAGER);
                progressEvent->SetRequestId(eventQueue->GetEventId());
                progressEvent->playTime = playerProgressPts;
                eventQueue->Push(progressEvent);

                lastUpdateProgressTime = playerProgressPts;
            }
            if(playerProgressPts - lastUpdateProgressTime >= 0.5){
                EventProgressRequest * progressEvent = new EventProgressRequest();
                progressEvent->SetFrom(EventTag::EVENT_PLAYER_CTR);
                progressEvent->SetTo(EventTag::EVENT_MANAGER);
                progressEvent->SetRequestId(eventQueue->GetEventId());
                progressEvent->playTime = playerProgressPts;
                eventQueue->Push(progressEvent);

                lastUpdateProgressTime = playerProgressPts;
            }


            if(videoFrame != nullptr){
                double pts = videoFrame->timePts;

                // qDebug() << "Video PTS:" << pts << "===Player Pts" << playerProgressPts;

                if(pts <= playerProgressPts){
                    EventUpdateUIRequest * event = new EventUpdateUIRequest();
                    event->SetFrom(EventTag::EVENT_PLAYER_CTR);
                    event->SetTo(EventTag::EVENT_MANAGER);
                    event->SetRequestId(eventQueue->GetEventId());
                    event->streamId = 0;
                    event->frame = nullptr;
                    eventQueue->Push(event);

                    playerVideoFrameQueue->Push(videoFrame);

                    videoFrame = nullptr;
                }
            }

            // 协助对 Video Frame 进行丢帧
            while(playerVideoFrameQueue->Size() > 3){
                Eyer::EyerAVFrame * f = nullptr;
                playerVideoFrameQueue->FrontPop(&f);
                if(f != nullptr){
                    delete f;
                }
            }

            if(audioFrame == nullptr){
                audioQueue1->FrontPop(&audioFrame);
            }

            if(audioFrame != nullptr){
                double pts = audioFrame->timePts;

                // qDebug() << "Audio PTS:" << pts << "===Player Pts" << playerProgressPts;

                if(pts <= playerProgressPts){
                    if(playerAudioFrameQueue != nullptr){
                        playerAudioFrameQueue->Push(audioFrame);
                        audioFrame = nullptr;
                    }
                }
            }

            // 协助对 Audio Frame 进行丢帧
            while(playerAudioFrameQueue->Size() > 3){
                Eyer::EyerAVFrame * f = nullptr;
                playerAudioFrameQueue->FrontPop(&f);
                if(f != nullptr){
                    delete f;
                }
            }



            // qDebug() << "Player Audio: " << playerAudioFrameQueue->Size() << endl;
            // qDebug() << "Player Video: " << playerVideoFrameQueue->Size() << endl;

        }

        startPlayerPts = playerProgressPts;

        // qDebug() << "Player THREAD End" << endl;

        SetStoping();
    }
}
