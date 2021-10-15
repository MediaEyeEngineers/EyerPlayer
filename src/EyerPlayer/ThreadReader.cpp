#include "ThreadReader.hpp"

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

#include "ThreadDecode.hpp"
#include "ThreadEventLoop.hpp"

namespace Eyer
{
    ThreadReader::ThreadReader(QueueBox * _queueBox, ThreadEventLoop * _eventLoop)
        : eventLoop(_eventLoop)
        , queueBox(_queueBox)
    {

    }

    ThreadReader::~ThreadReader()
    {

    }

    void ThreadReader::Run()
    {
        EyerLog("ThreadReader Start\n");

        Eyer::EyerAVReader reader("/Users/miaoyuqiao/Desktop/HDR/1080_1920_HDR_Color_Card.mp4");
        int ret = reader.Open();
        if(ret){
            // 打开失败
            // eventLoop->PushEvent()
        }

        int streamCount = reader.GetStreamCount();
        EyerLog("Stream Count: %d\n", streamCount);

        int videoStreamIndex = reader.GetVideoStreamIndex();
        EyerLog("Video Stream Index: %d\n", videoStreamIndex);

        int audioStreamIndex = reader.GetAudioStreamIndex();
        EyerLog("Audio Stream Index: %d\n", audioStreamIndex);

        EyerAVStream videoStream = reader.GetStream(videoStreamIndex);
        EyerAVStream audioStream = reader.GetStream(audioStreamIndex);

        queueBox->AddStream(audioStream);
        queueBox->AddStream(videoStream);
        queueBox->StartDeocder();

        std::unique_lock<std::mutex> locker(queueBox->mtx);
        // 该线程用于读取视频流
        while(!stopFlag) {
            // 缓存 1MB
            int maxCahceSize = 1024 * 1024;
            while(!stopFlag && queueBox->GetPacketQueueCacheSize() >= maxCahceSize) {
                queueBox->cv.wait(locker);
            }

            if(queueBox->GetPacketQueueCacheSize() < maxCahceSize){
                EyerAVPacket * packet = new EyerAVPacket();
                int ret = reader.Read(*packet);
                if(ret){
                    // 读取失败或者网络出错
                    if(packet != nullptr){
                        delete packet;
                        packet = nullptr;
                    }
                    break;
                }

                EyerLog("pts: %lld\n", packet->GetPTS());
                queueBox->PutPacket(packet);

                if(packet != nullptr){
                    delete packet;
                    packet = nullptr;
                }
            }
        }

        queueBox->StopDecoder();
        EyerLog("ThreadReader End\n");
    }

    int ThreadReader::SetStopFlag(){
        std::unique_lock<std::mutex> locker(queueBox->mtx);
        stopFlag = 1;
        queueBox->cv.notify_all();
        return 0;
    }
}