#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"

#include "PlayerEvent.hpp"

namespace EyerPlayer {
    AVReaderThread::AVReaderThread(Eyer::EyerString _url, long long _openEventId, Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _frameQueueManager)
    {
        url = _url;
        openEventId = _openEventId;
        eventQueue = _eventQueue;

        frameQueueManager = _frameQueueManager;
    }

    AVReaderThread::~AVReaderThread()
    {
        if(videoThread != nullptr){
            videoThread->Stop();
            delete videoThread;
            videoThread = nullptr;
        }
        if(audioThread != nullptr){
            audioThread->Stop();
            delete audioThread;
            audioThread = nullptr;
        }

        if(frameQueueManager != nullptr){
            frameQueueManager->ClearAndDelete();
            delete frameQueueManager;
            frameQueueManager = nullptr;
        }
    }

    int AVReaderThread::SetGLCtx(Eyer::EyerGLContextThread * _glCtx)
    {
        glCtx = _glCtx;
        return 0;
    }

    void AVReaderThread::Run()
    {
        EyerLog("AVReader Thread Start\n");

        EventOpenResponse * event = nullptr;
        MediaInfo mediaInfo;
        int videoStreamIndex = -1;
        int audioStreamIndex = -1;

        
        Eyer::EyerAVReader reader(url);
        int ret = reader.Open();

        if(ret){
            EyerLog("AVReader Thread Open Error: %d\n", ret);

            event = new EventOpenResponse();
            event->SetFrom(EventTag::EVENT_AVREADER);
            event->SetTo(EventTag::EVENT_MANAGER);
            event->SetRequestId(openEventId);
            event->status = EventOpenStatus::OPEN_STATUS_FAIL;
            eventQueue->Push(event);

            goto END;
        }

        // 获取视频流编号
        videoStreamIndex = reader.GetVideoStreamIndex();
        if(videoStreamIndex >= 0){
            Eyer::EyerAVStream videoStream;
            reader.GetStream(videoStream, videoStreamIndex);

            Eyer::EyerAVRational timebase;
            reader.GetStreamTimeBase(timebase, videoStreamIndex);

            // 返回视频流信息到 MediaInfo
            mediaInfo.videoStream.SetWH(videoStream.GetWidth(), videoStream.GetHeight());

            // 创建视频解码线程
            videoThread = new AVDecoderThread(&videoStream, timebase, Eyer::EyerAVStreamType::STREAM_TYPE_VIDEO, frameQueueManager);
            videoThread->Start();
        }
        // 获取音频流编号
        audioStreamIndex = reader.GetAudioStreamIndex();
        if(audioStreamIndex >= 0){
            Eyer::EyerAVStream audioStream;
            reader.GetStream(audioStream, audioStreamIndex);

            Eyer::EyerAVRational timebase;
            reader.GetStreamTimeBase(timebase, audioStreamIndex);

            // 创建音频解码线程
            audioThread = new AVDecoderThread(&audioStream, timebase, Eyer::EyerAVStreamType::STREAM_TYPE_AUDIO, frameQueueManager);
            audioThread->Start();
        }

        event = new EventOpenResponse();
        event->SetFrom(EventTag::EVENT_AVREADER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(openEventId);
        event->status = EventOpenStatus::OPEN_STATUS_SUCCESS;
        event->mediaInfo = mediaInfo;
        eventQueue->Push(event);

        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);

            int cacheSize = videoThread->GetPacketSize() + audioThread->GetPacketSize();
            // EyerLog("Cache Size: %d\n", cacheSize);
            if(cacheSize >= 1024 * 1024 * 10){
                continue;
            }

            Eyer::EyerAVPacket * packet = new Eyer::EyerAVPacket();
            ret = reader.Read(packet);

            if(ret){
                // 读取错误 或者 视频结束
                if(packet != nullptr){
                    delete packet;
                    packet = nullptr;
                }
                goto END;
            }

            if(packet->GetStreamId() == videoStreamIndex){
                videoThread->SendPacket(packet);
            }
            else if(packet->GetStreamId() == audioStreamIndex){
                audioThread->SendPacket(packet);
            }
            else{
                delete packet;
            }
        }

    END:
        //销毁两个线程
        if(videoThread != nullptr){
            videoThread->Stop();
            delete videoThread;
            videoThread = nullptr;
        }
        if(audioThread != nullptr){
            audioThread->Stop();
            delete audioThread;
            audioThread = nullptr;
        }

        EyerLog("AVReader Thread Stop\n");
    }
}
