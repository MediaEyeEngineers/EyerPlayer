#include "ThreadReader.hpp"

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

#include "ThreadEventLoop.hpp"

namespace Eyer
{
    ThreadReader::ThreadReader(const EyerString & _url, ThreadEventLoop * _eventLoop)
        : eventLoop(_eventLoop)
        , url(_url)
    {

    }

    ThreadReader::~ThreadReader()
    {

    }

    void ThreadReader::Run()
    {
        EyerLog("ThreadReader Start\n");
        EyerLog("ThreadReader Open Url: %s\n", url.str);

        decoderBox = new DecoderBox();
        reader = new EyerAVReader(url);
        int ret = reader->Open();
        if(ret){
            // 打开失败
            // 抛出错误，线程进入待命状态
            EyerLog("Open Fail\n");
            return;
        }
        else {
            int streamCount = reader->GetStreamCount();
            int videoStreamIndex = reader->GetVideoStreamIndex();
            int audioStreamIndex = reader->GetAudioStreamIndex();

            EyerLog("Stream Count: %d\n", streamCount);
            EyerLog("Duration: %f\n", reader->GetDuration());
            EyerLog("Video Stream Index: %d\n", videoStreamIndex);
            EyerLog("Audio Stream Index: %d\n", audioStreamIndex);

            if(videoStreamIndex >= 0){
                const EyerAVStream & videoStream = reader->GetStream(videoStreamIndex);
                decoderBox->AddStream(videoStream);
            }
            if(audioStreamIndex >= 0){
                const EyerAVStream & audioStream = reader->GetStream(audioStreamIndex);
                decoderBox->AddStream(audioStream);
            }
            decoderBox->StartDeocder();

            playCtr = new ThreadPlayCtr(decoderBox, eventLoop);
            playCtr->Start();
        }

        while(!stopFlag) {
            int maxCacheSize = 1024 * 1024 * 5;

            std::unique_lock<std::mutex> locker(decoderBox->cvBox.mtx);
            while(!stopFlag && (decoderBox->GetPacketCacheSize() >= maxCacheSize)){
                decoderBox->cvBox.cv.wait(locker);
            }

            // EyerLog("Size: %d\n", decoderBox->GetPacketCacheSize());

            EyerAVPacket * packet = new EyerAVPacket();

            locker.unlock();
            ret = reader->Read(packet);
            locker.lock();
            if(ret){
                // 出错
                if(packet != nullptr){
                    delete packet;
                    packet = nullptr;
                }
                continue;
            }
            ret = decoderBox->PutPacket(packet);
            if(ret){
                // 插入失败，删除 packet
                if(packet != nullptr){
                    delete packet;
                    packet = nullptr;
                }
            }
            else {
                // 插入成功，通知
                decoderBox->cvBox.cv.notify_all();
            }
        }

        if(playCtr != nullptr){
            playCtr->Stop();
            delete playCtr;
            playCtr = nullptr;
        }
        if(reader != nullptr){
            delete reader;
            reader = nullptr;
        }
        if(decoderBox != nullptr){
            decoderBox->StopDecoder();
            delete decoderBox;
            decoderBox = nullptr;
        }

        EyerLog("ThreadReader End\n");
    }

    int ThreadReader::SetStopFlag(){
        std::unique_lock<std::mutex> locker(decoderBox->cvBox.mtx);
        stopFlag = 1;
        decoderBox->cvBox.cv.notify_all();
        return 0;
    }

    int ThreadReader::SetStartEventLoopFlag()
    {
        std::unique_lock<std::mutex> locker(decoderBox->cvBox.mtx);
        eventLoopFlag = 1;
        decoderBox->cvBox.cv.notify_all();
        return 0;
    }
}