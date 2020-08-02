#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"

namespace EyerPlayer {
    PlayCtrThread::PlayCtrThread(AVFrameQueueManager * _frameQueueManager)
    {
        frameQueueManager = _frameQueueManager;
    }

    PlayCtrThread::~PlayCtrThread()
    {
    }

    void PlayCtrThread::Run()
    {
        EyerLog("PlayCtr Thread Start\n");

        AVFrameQueue * videoFrameQueue = nullptr;
        AVFrameQueue * audioFrameQueue = nullptr;

        frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_VIDEO, &videoFrameQueue);
        frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_AUDIO, &audioFrameQueue);

        long long startTime = Eyer::EyerTime::GetTime();

        
        Eyer::EyerAVFrame * videoFrame = nullptr;
        Eyer::EyerAVFrame * audioFrame = nullptr;

        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);

            long long nowTime = Eyer::EyerTime::GetTime();

            double dTime = (nowTime - startTime) / 1000.0;
            


            if(videoFrame == nullptr){
                if(videoFrameQueue != nullptr){
                    videoFrameQueue->FrontPop(&videoFrame);
                }
            }
            if(videoFrame != nullptr){
                // 判断视频是否应该播放
                if(videoFrame->timePts <= dTime){
                    // Play !!!
                    if(glCtx != nullptr){
                        glCtx->AddTaskToRenderAndFreeQueue();
                    }
                    // EyerLog("Video Frame: %f\n", videoFrame->timePts);
                    if(videoFrame != nullptr){
                        delete videoFrame;
                        videoFrame = nullptr;
                    }
                }
            }
            
            

            
            if(audioFrame == nullptr){
                if(audioFrameQueue != nullptr){
                    audioFrameQueue->FrontPop(&audioFrame);
                }
            }
            if(audioFrame != nullptr){
                // 判断音频是否应该播放
                if(audioFrame->timePts <= dTime){
                    // Play !!!
                    // EyerLog("Audio Frame: %f\n", audioFrame->timePts);
                    if(audioFrame != nullptr){
                        delete audioFrame;
                        audioFrame = nullptr;
                    }
                }
            }

            // Eyer::EyerTime::EyerSleepMilliseconds(1000);
        }
        EyerLog("PlayCtr Thread End\n");
    }

    int PlayCtrThread::SetGLCtx(Eyer::EyerGLContextThread * _glCtx)
    {
        glCtx = _glCtx;
        return 0;
    }
}