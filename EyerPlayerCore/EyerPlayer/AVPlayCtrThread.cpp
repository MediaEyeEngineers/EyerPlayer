#include "EyerGLRenderTask/YUVRenderTask.hpp"
#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"
#include "EyerOpenSL/EyerOpenSL.hpp"

namespace Eyer {
    AVPlayCtrThread::AVPlayCtrThread(AVFrameQueueManager * _frameQueueManager, double _videoTime)
    {
        videoTime = _videoTime;
        frameQueueManager = _frameQueueManager;

        opensl = new EyerOpenSL();
    }

    AVPlayCtrThread::~AVPlayCtrThread()
    {
        if(opensl != nullptr){
            delete opensl;
            opensl = nullptr;
        }
    }

    void AVPlayCtrThread::Run()
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

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
        long long videoFrameTime = 0;

        long long pauseingTime = 0;
        while(!stopFlag){

            Eyer::EyerTime::EyerSleepMilliseconds(1);

            if(status == AVPlayCtrStatus::STATUS_PAUSEING){
                long long pauseStart = Eyer::EyerTime::GetTime();
                while(!stopFlag){
                    Eyer::EyerTime::EyerSleepMilliseconds(100);
                    if(status == AVPlayCtrStatus::STATUS_PLAYING){
                        break;
                    }
                }
                long long pauseEnd = Eyer::EyerTime::GetTime();

                pauseingTime += (pauseEnd - pauseStart);
            }

            long long nowTime = Eyer::EyerTime::GetTime() - pauseingTime;

            double dTime = (nowTime - startTime) / 1000.0;
            videoTime = dTime;

            if(mediaCodec == nullptr){
                frameQueueManager->GetMediaCodecQueue(&mediaCodec);
            }

            if(mediaCodec != nullptr){
                if(outindex < 0){
                    outindex = mediaCodec->dequeueOutputBuffer(1000 * 1);
                    if(outindex >= 0){
                        videoFrameTime = mediaCodec->getOutTime();
                    }
                }

                if(outindex >= 0){
                    double timePts = videoFrameTime / 1000.0;
                    if (timePts <= dTime) {
                        mediaCodec->releaseOutputBuffer(outindex, true);
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
                    if(audioFrame != nullptr){
                        opensl->PutFrame(audioFrame);
                        audioFrame = nullptr;
                    }
                }
            }
        }

        Eyer::EyerJNIEnvManager::jvm->DetachCurrentThread();

        EyerLog("PlayCtr Thread End\n");
    }

    int AVPlayCtrThread::SetStatus(AVPlayCtrStatus _status)
    {
        statusMut.lock();
        status = _status;
        statusMut.unlock();
        return 0;
    }

    int AVPlayCtrThread::SetGLCtx(Eyer::EyerGLContextThread * _glCtx)
    {
        mut.lock();
        glCtx = _glCtx;
        mut.unlock();
        return 0;
    }

    double AVPlayCtrThread::GetVideoTime()
    {
        return videoTime;
    }
}