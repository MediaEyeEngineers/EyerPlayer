#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"

#include "PlayerEvent.hpp"

namespace Eyer {
    AVReaderThread::AVReaderThread(Eyer::EyerString _url, long long _openEventId, Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _frameQueueManager)
        : reader(_url)
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
    }

    int AVReaderThread::SetGLCtx(Eyer::EyerGLContextThread * _glCtx)
    {
        glCtx = _glCtx;
        return 0;
    }

    int AVReaderThread::SetSurface(jobject _surface)
    {
        surface = _surface;
        return 0;
    }

    AVReaderStatus AVReaderThread::GetAVReaderStatus()
    {
        return status;
    }

    int AVReaderThread::GetMediaInfo(MediaInfo & _mediaInfo)
    {
        _mediaInfo = mediaInfo;
        return 0;
    }

    int AVReaderThread::Seek(double time)
    {
        if(audioThread != nullptr){
            EyerLog("Audio Decoder Seek Start\n");
            SEEK_Decoder_Runnable seekDecoderRunnable(audioThread);
            audioThread->PushEvent(&seekDecoderRunnable);
            audioThread->StartEventLoop();
            audioThread->StopEventLoop();
            EyerLog("Audio Decoder Seek End\n");
        }
        if(videoThread != nullptr){
            EyerLog("Video Decoder Seek Start\n");
            SEEK_Decoder_Runnable seekDecoderRunnable(videoThread);
            videoThread->PushEvent(&seekDecoderRunnable);
            videoThread->StartEventLoop();
            videoThread->StopEventLoop();
            EyerLog("Video Decoder Seek End\n");
        }

        EyerLog("Reader Seek Start\n");
        reader.Seek(time);
        EyerLog("Reader Seek End\n");

        return 0;
    }

    void AVReaderThread::Run()
    {
        EyerLog("AVReader Thread Start\n");

        EventOpenResponse * event = nullptr;
        int videoStreamIndex = -1;
        int audioStreamIndex = -1;

        double duration = 0.0;


        int ret = reader.Open();

        if(ret){
            EyerLog("AVReader Thread Open Error: %d\n", ret);

            status = AVReaderStatus::READER_STATUS_OPEN_FAIL;

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
            videoThread = new AVDecoderThreadMediaCodec(videoStream, frameQueueManager, surface);
            // videoThread = new AVDecoderThreadSoftware(videoStream, frameQueueManager);
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
            audioThread = new AVDecoderThreadSoftware(audioStream, frameQueueManager);
            audioThread->Start();
        }

        status = AVReaderStatus::READER_STATUS_OPEN_SUCCESS;

        duration = reader.GetDuration();
        mediaInfo.SetDuration(duration);

        event = new EventOpenResponse();
        event->SetFrom(EventTag::EVENT_AVREADER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(openEventId);
        event->status = EventOpenStatus::OPEN_STATUS_SUCCESS;
        event->mediaInfo = mediaInfo;
        eventQueue->Push(event);

        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);

            EventLoop();

            int cacheSize = videoThread->GetPacketSize() + audioThread->GetPacketSize();
            // EyerLog("Cache Size: %d\n", cacheSize);
            if(cacheSize >= 1024 * 1024 * 2){
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

                // 发送一个空的 packet 出去
                packet = new Eyer::EyerAVPacket();
                packet->SetLast();
                videoThread->SendPacket(packet);

                continue;
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
