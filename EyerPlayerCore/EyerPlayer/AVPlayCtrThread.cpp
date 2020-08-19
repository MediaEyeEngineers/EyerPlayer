#include "EyerGLRenderTask/YUVRenderTask.hpp"
#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"

namespace EyerPlayer {
    AVPlayCtrThread::AVPlayCtrThread(AVFrameQueueManager * _frameQueueManager)
    {
        frameQueueManager = _frameQueueManager;
    }

    AVPlayCtrThread::~AVPlayCtrThread()
    {
    }

    void AVPlayCtrThread::Run()
    {
        EyerLog("PlayCtr Thread Start\n");

        AVFrameQueue * videoFrameQueue = nullptr;
        AVFrameQueue * audioFrameQueue = nullptr;

        frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_VIDEO, &videoFrameQueue);
        frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_AUDIO, &audioFrameQueue);

        long long startTime = Eyer::EyerTime::GetTime();

        Eyer::EyerAVFrame * videoFrame = nullptr;
        Eyer::EyerAVFrame * audioFrame = nullptr;

        Eyer::EyerMediaCodec * mediaCodec = nullptr;
        int outindex = -1;
        long videoFrameTime = 0;

        while(!stopFlag){

            Eyer::EyerTime::EyerSleepMilliseconds(1);

            long long nowTime = Eyer::EyerTime::GetTime();

            double dTime = (nowTime - startTime) / 1000.0;

            if(mediaCodec == nullptr){
                frameQueueManager->GetMediaCodecQueue(&mediaCodec);
            }

            if(mediaCodec != nullptr){
                if(outindex < 0){
                    outindex = mediaCodec->DequeueOutputBuffer();
                    videoFrameTime = mediaCodec->GetOutTime();
                }

                if(outindex >= 0){
                    double timePts = videoFrameTime / 1000.0;
                    if (timePts <= dTime) {
                        mediaCodec->RenderFrame(outindex);
                        outindex = -1;
                    }
                }
            }


            /*
            if(videoFrame == nullptr){
                if(videoFrameQueue != nullptr){
                    videoFrameQueue->FrontPop(&videoFrame);
                }
            }
            if(videoFrame != nullptr){
                // 判断视频是否应该播放
                if(videoFrame->timePts <= dTime){
                    mut.lock();
                    if(glCtx != nullptr){
                        YUVRenderTask * yuvRenderTask = new YUVRenderTask();
                        yuvRenderTask->SetFrame(videoFrame);
                        glCtx->AddRenderTask(yuvRenderTask);
                        videoFrame = nullptr;
                    }
                    mut.unlock();

                    if(videoFrame != nullptr){
                        delete videoFrame;
                        videoFrame = nullptr;
                    }
                }
            }
            */





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
        }

        Eyer::EyerJNIEnvManager::jvm->DetachCurrentThread();
        EyerLog("PlayCtr Thread End\n");
    }

    int AVPlayCtrThread::SetGLCtx(Eyer::EyerGLContextThread * _glCtx)
    {
        mut.lock();
        glCtx = _glCtx;
        mut.unlock();
        return 0;
    }
}