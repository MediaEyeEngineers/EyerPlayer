#include "ThreadReader.hpp"

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

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

        // Eyer::EyerString path = "/Users/miaoyuqiao/Desktop/HDR/color_card_hevc_3840x2160_yuv420p10le_hlg_bt2020_rotate_270.MOV";
        // Eyer::EyerString path = "/Users/miaoyuqiao/Desktop/HDR/1080_1920_HDR_Color_Card.mp4";
        // Eyer::EyerString path = "/Users/miaoyuqiao/Desktop/HDR/ZhongLi.mp4";
        // Eyer::EyerString path = "/Users/miaoyuqiao/Desktop/HDR/ip13.mp4";
        Eyer::EyerString path = "/Users/yuqiaomiao/Downloads/demo.mp4";

        Eyer::EyerAVReader reader(path);
        int ret = reader.Open();
        if(ret){
            // 打开失败
            // eventLoop->PushEvent()
            EyerLog("Open Fail\n");
        }

        int streamCount = reader.GetStreamCount();
        EyerLog("Stream Count: %d\n", streamCount);

        int videoStreamIndex = reader.GetVideoStreamIndex();
        EyerLog("Video Stream Index: %d\n", videoStreamIndex);

        int audioStreamIndex = reader.GetAudioStreamIndex();
        EyerLog("Audio Stream Index: %d\n", audioStreamIndex);

        const EyerAVStream & videoStream = reader.GetStream(videoStreamIndex);
        const EyerAVStream & audioStream = reader.GetStream(audioStreamIndex);

        queueBox->AddStream(audioStream);
        queueBox->AddStream(videoStream);
        queueBox->StartDeocder();

        // 开始播放控制线程
        ThreadPlayCtr playCtr(queueBox, eventLoop);
        playCtr.Start();

        // 该线程用于读取视频流
        while(!stopFlag) {
            std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
            // 缓存 1MB
            int maxCahceSize = 1024 * 1024;
            while(!stopFlag && queueBox->GetPacketQueueCacheSize() >= maxCahceSize) {
                queueBox->cvBox.cv.wait(locker);
            }

            if(queueBox->GetPacketQueueCacheSize() >= maxCahceSize){
                continue;
            }

            locker.unlock();

            EyerAVPacket * packet = new EyerAVPacket();
            int ret = reader.Read(packet);
            if(ret){
                // 读取出错
                if(packet != nullptr) {
                    delete packet;
                    packet = nullptr;
                }
                continue;
            }

            locker.lock();
            ret = queueBox->PutPacket(packet);
            if(ret == 0){
                queueBox->cvBox.cv.notify_all();
            } else {
                // 插入失败
                if(packet != nullptr) {
                    delete packet;
                    packet = nullptr;
                }
            }
            locker.unlock();
        }

        playCtr.Stop();

        queueBox->StopDecoder();
        EyerLog("ThreadReader End\n");
    }

    int ThreadReader::SetStopFlag(){
        std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
        stopFlag = 1;
        queueBox->cvBox.cv.notify_all();
        return 0;
    }
}