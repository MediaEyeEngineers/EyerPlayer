#include "EyerPlayerThread.hpp"
#include "PlayerEvent.hpp"

#include <QDebug>

namespace EyerPlayer {
    PlayCtrThread::PlayCtrThread(Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _queueManager)
    {
        eventQueue = _eventQueue;
        queueManager = _queueManager;
    }

    PlayCtrThread::~PlayCtrThread()
    {

    }

    void PlayCtrThread::Run()
    {
        double audioPts = 0.0;

        AVFrameQueue * videoQueue = nullptr;
        AVFrameQueue * audioQueue1 = nullptr;
        AVFrameQueue * audioQueue2 = nullptr;

        int videoStreamId = 0;
        int audioStreamId1 = 1;
        int audioStreamId2 = 2;

        {
            Eyer::EyerString queueKey = Eyer::EyerString(EventTag::FRAME_QUEUE_DECODER_VIDEO) + Eyer::EyerString::Number(videoStreamId);
            queueManager->GetQueue(queueKey, &videoQueue);
            if(videoQueue == nullptr){
                qDebug() << "Decoder Thread Get Frame Queue Fail" << endl;
            }
        }

        {
            Eyer::EyerString queueKey = Eyer::EyerString(EventTag::FRAME_QUEUE_DECODER_VIDEO) + Eyer::EyerString::Number(audioStreamId1);
            queueManager->GetQueue(queueKey, &audioQueue1);
            if(audioQueue1 == nullptr){
                qDebug() << "Decoder Thread Get Frame Queue Fail" << endl;
            }
        }

        {
            Eyer::EyerString queueKey = Eyer::EyerString(EventTag::FRAME_QUEUE_DECODER_VIDEO) + Eyer::EyerString::Number(audioStreamId2);
            queueManager->GetQueue(queueKey, &audioQueue2);
            if(audioQueue2 == nullptr){
                qDebug() << "Decoder Thread Get Frame Queue Fail" << endl;
            }
        }


        SetRunning();

        long long lastRenderTime = -1;
        double lastPTS = 0;

        Eyer::EyerAVFrame * videoFrame = nullptr;

        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            if(videoFrame == nullptr){
                videoQueue->FrontPop(&videoFrame);
            }

            if(videoFrame != nullptr){
                double pts = videoFrame->timePts;

                // qDebug() << pts << "===" << audioPts << endl;
                if(pts <= audioPts){
                    EventUpdateUIRequest * event = new EventUpdateUIRequest();
                    event->SetFrom(EventTag::EVENT_PLAYER_CTR);
                    event->SetTo(EventTag::EVENT_MANAGER);
                    event->SetRequestId(eventQueue->GetEventId());
                    event->streamId = 0;
                    event->frame = videoFrame;
                    eventQueue->Push(event);

                    lastRenderTime = Eyer::EyerTime::GetTime();
                    lastPTS = pts;

                    videoFrame = nullptr;
                }
            }
            {

                AVFrameQueue * playerAudioFrameQueue = nullptr;
                queueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_AUDIO, &playerAudioFrameQueue);
                if(playerAudioFrameQueue != nullptr){
                    if(playerAudioFrameQueue->Size() <= 1) {
                        Eyer::EyerAVFrame * audioFrame = nullptr;
                        audioQueue1->FrontPop(&audioFrame);
                        if(audioFrame != nullptr){
                            playerAudioFrameQueue->Push(audioFrame);

                            audioPts = audioFrame->timePts;
                        }
                    }
                }
            }

            {
                Eyer::EyerAVFrame * audioFrame = nullptr;
                audioQueue2->FrontPop(&audioFrame);
                if(audioFrame != nullptr){
                    delete audioFrame;
                }
            }
        }

        SetStoping();
    }
}
