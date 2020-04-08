#include "EyerPlayerThread.hpp"
#include "PlayerEvent.hpp"

#include <QDebug>

namespace EyerPlayer {
    PlayCtrThread::PlayCtrThread(Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _queueManager, int _recommendVideoIndex, int _recommendAudioIndex)
    {
        recommendVideoIndex = _recommendVideoIndex;
        recommendAudioIndex = _recommendAudioIndex;
        eventQueue = _eventQueue;
        queueManager = _queueManager;
    }

    PlayCtrThread::~PlayCtrThread()
    {
        // TODO 回收所有的缓冲帧
    }

    void PlayCtrThread::Run()
    {
        SetRunning();

        double startPlayerPts = 0.0;
        double playerPts = 0.0;
        long long startTime = Eyer::EyerTime::GetTime();

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

        Eyer::EyerAVFrame * videoFrame = nullptr;
        Eyer::EyerAVFrame * audioFrame = nullptr;

        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            long long nowTime = Eyer::EyerTime::GetTime();
            double dTime = (nowTime - startTime) / 1000.0;
            playerPts = startPlayerPts + dTime;

            if(videoFrame == nullptr){
                videoQueue->FrontPop(&videoFrame);
            }

            if(videoFrame != nullptr){
                double pts = videoFrame->timePts;

                if(pts <= playerPts){
                    EventUpdateUIRequest * event = new EventUpdateUIRequest();
                    event->SetFrom(EventTag::EVENT_PLAYER_CTR);
                    event->SetTo(EventTag::EVENT_MANAGER);
                    event->SetRequestId(eventQueue->GetEventId());
                    event->streamId = 0;
                    event->frame = videoFrame;
                    eventQueue->Push(event);

                    videoFrame = nullptr;
                }
            }

            // 协助对 Video Frame 进行丢帧
            AVFrameQueue * playerVideoFrameQueue = nullptr;
            queueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_VIDEO, &playerVideoFrameQueue);
            if(playerVideoFrameQueue == nullptr){
                return;
            }

            while(playerVideoFrameQueue->Size() > 5){
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
                if(pts <= playerPts){
                    AVFrameQueue * playerAudioFrameQueue = nullptr;
                    queueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_AUDIO, &playerAudioFrameQueue);
                    if(playerAudioFrameQueue != nullptr){
                        playerAudioFrameQueue->Push(audioFrame);
                        audioFrame = nullptr;
                    }
                }
            }
        }

        SetStoping();
    }
}
