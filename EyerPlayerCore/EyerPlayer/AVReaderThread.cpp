#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"

#include "PlayerEvent.hpp"

namespace Eyer {
    AVReaderThread::AVReaderThread(Eyer::EyerString _url, const EyerPlayerConfig & _playerConfig, long long _openEventId, Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _frameQueueManager)
    {
        url = _url;
        openEventId = _openEventId;
        eventQueue = _eventQueue;

        frameQueueManager = _frameQueueManager;

        playerConfig = _playerConfig;

        reader = new EyerAVReader(url);
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
        if(reader != nullptr){
            delete reader;
            reader = nullptr;
        }
    }

    int AVReaderThread::SetSurface(jobject _surface)
    {
        surface = _surface;
        return 0;
    }


    int AVReaderThread::Seek(double time)
    {
        EyerLog("Reader Seek Start\n");
        if(reader != nullptr){
            reader->Seek(time);
        }
        EyerLog("Reader Seek End\n");

        EyerLog("Reader Seek Decoder Start\n");
        if(audioThread != nullptr){
            SEEK_Decoder_Runnable seekDecoderRunnable(audioThread);
            audioThread->PushEvent(&seekDecoderRunnable);
            audioThread->StartEventLoop();
        }
        if(videoThread != nullptr){
            SEEK_Decoder_Runnable seekDecoderRunnable(videoThread);
            videoThread->PushEvent(&seekDecoderRunnable);
            videoThread->StartEventLoop();
        }

        if(audioThread != nullptr){
            audioThread->StopEventLoop();
        }
        if(videoThread != nullptr){
            videoThread->StopEventLoop();
        }

        EyerLog("Reader Seek Decoder End\n");

        return 0;
    }

    const MediaInfo AVReaderThread::GetMediaInfo()
    {
        return mediaInfo;
    }

    void AVReaderThread::Run()
    {
        EyerLog("AVReader Thread Start\n");

        int videoStreamIndex = -1;
        int audioStreamIndex = -1;

        EventOpenResponse * event = nullptr;

        int ret = reader->Open();
        if(ret){
            // 打开出错
            EyerLog("AVReader Thread Open Error: %d\n", ret);
            event = new EventOpenResponse();
            event->SetFrom(EventTag::EVENT_AVREADER);
            event->SetTo(EventTag::EVENT_MANAGER);
            event->SetRequestId(openEventId);
            event->status = EventOpenStatus::OPEN_STATUS_FAIL;
            eventQueue->Push(event);

            goto END;
        }

        mediaInfo.duration = reader->GetDuration();

        // 获取视频流编号
        videoStreamIndex = reader->GetVideoStreamIndex();

        if(videoStreamIndex >= 0){

            Eyer::EyerAVStream videoStream;
            reader->GetStream(videoStream, videoStreamIndex);
            Eyer::EyerAVRational timebase;
            reader->GetStreamTimeBase(timebase, videoStreamIndex);

            // 返回视频流信息到 MediaInfo
            mediaInfo.videoStream.width = videoStream.GetWidth();
            mediaInfo.videoStream.height = videoStream.GetHeight();

            if(videoThread == nullptr){
                // 创建视频解码线程
                if(playerConfig.videoDecoder == EyerVideoDecoder::SOFTWORE){
                    videoThread = new AVDecoderThreadSoftware(videoStream, frameQueueManager);
                }
                else if(playerConfig.videoDecoder == EyerVideoDecoder::MEDIACODEC){
                    videoThread = new AVDecoderThreadMediaCodec(videoStream, frameQueueManager, surface);
                }

                videoThread = new AVDecoderThreadSoftware(videoStream, frameQueueManager);
                videoThread->Start();
            }
        }

        // 获取音频流编号
        audioStreamIndex = reader->GetAudioStreamIndex();
        if(audioStreamIndex >= 0){

            Eyer::EyerAVStream audioStream;
            reader->GetStream(audioStream, audioStreamIndex);
            Eyer::EyerAVRational timebase;
            reader->GetStreamTimeBase(timebase, audioStreamIndex);

            mediaInfo.audioStream.audioChannels = audioStream.GetAudioChannels();
            mediaInfo.audioStream.audioSampleRate = audioStream.GetAudioSampleRate();

            if(audioThread == nullptr){
                // 创建音频解码线程
                audioThread = new AVDecoderThreadSoftware(audioStream, frameQueueManager);
                audioThread->Start();
            }
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

            EventLoop();

            // TODO 判断音频的缓存
            int videoCacheSize = videoThread->GetPacketSize();
            if(videoCacheSize >= 1024 * 1024 * 1){
                continue;
            }

            Eyer::EyerAVPacket * packet = new Eyer::EyerAVPacket();
            ret = reader->Read(packet);

            if(ret){
                // 读取错误 或者 视频结束，先只处理视频结束的场景
                if(packet != nullptr){
                    delete packet;
                    packet = nullptr;
                }

                // 发送一个空的 packet 出去

                // 视频结束，线程不停。等待 Seek 或其他操作。
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
        EyerLog("AVReader Thread Stop\n");
    }
}
