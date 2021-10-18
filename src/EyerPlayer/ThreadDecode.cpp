#include "ThreadDecode.hpp"

#include "EyerCore/EyerCore.hpp"
#include "QueueBox.hpp"
#include "EyerAV/EyerAV.hpp"

namespace Eyer
{
    ThreadDecode::ThreadDecode(const Eyer::EyerAVStream & _stream, QueueBox * _queueBox)
        : stream(_stream)
        , queueBox(_queueBox)
    {
    }

    ThreadDecode::~ThreadDecode()
    {

    }

    int ThreadDecode::GetStreamId()
    {
        return stream.GetStreamId();
    }

    int ThreadDecode::PutPacket(EyerAVPacket * packet)
    {
        packetQueue.PushLock(packet);
        packetCacheSize += packet->GetSize();
        return 0;
    }

    void ThreadDecode::Run()
    {
        EyerLog("ThreadDecode Start\n");
        // 该线程用于解码

        // 初始化解码器
        Eyer::EyerAVDecoder decoder;
        int ret = decoder.Init(stream);
        if(ret){
            EyerLog("Init Decoder Fail\n");
        }

        while(!stopFlag) {
            std::unique_lock<std::mutex> locker(queueBox->mtx);
            while(!stopFlag && packetQueue.SizeLock() <= 0) {
                queueBox->cv.wait(locker);
            }

            EyerAVPacket * packet = nullptr;
            packetQueue.Lock();
            int size = packetQueue.Size();
            if(size > 0) {
                packet = packetQueue.FrontPop();
            }
            packetQueue.Unlock();

            if(packet == nullptr){
                continue;
            }

            packetCacheSize -= packet->GetSize();
            queueBox->cv.notify_all();

            locker.unlock();

            decoder.SendPacket(*packet);
            while(1){
                EyerAVFrame frame;
                ret = decoder.RecvFrame(frame);
                if(ret){
                    break;
                }

                EyerLog("Frame: %f\n", frame.GetSecPTS());
            }
        }

        EyerLog("ThreadDecode End\n");
    }

    int ThreadDecode::SetStopFlag(){
        std::unique_lock<std::mutex> locker(queueBox->mtx);
        stopFlag = 1;
        queueBox->cv.notify_all();
        return 0;
    }
}