#include "EyerDecodeQueueFFmpeg.hpp"

namespace Eyer
{
    EyerDecodeQueueFFmpeg::EyerDecodeQueueFFmpeg(const EyerAVStream & avStream)
        : EyerDecodeQueueBase(avStream)
    {

    }

    EyerDecodeQueueFFmpeg::~EyerDecodeQueueFFmpeg()
    {

    }

    int EyerDecodeQueueFFmpeg::StartDecoder()
    {
        Start();
        return 0;
    }

    int EyerDecodeQueueFFmpeg::StopDeocder()
    {
        Stop();
        return 0;
    }

    void EyerDecodeQueueFFmpeg::Run()
    {
        EyerLog("EyerDecodeQueueFFmpeg Start, Stream Id: %d\n", avStream.GetStreamId());

        EyerAVDecoder decoder;
        int ret = decoder.Init(avStream);
        if(ret){
            EyerLog("Decoder Init Error\n");
        }

        while(1){
            if(stopFlag){
                break;
            }

            if(packetQueue.SizeLock() <= 0){
                continue;
            }

            // 尝试取出一个 Packet
            EyerAVPacket * avPacket = nullptr;
            // Frame 缓存池
            packetQueue.Lock();
            if(packetQueue.Size() > 0){
                avPacket = packetQueue.FrontPop();
            }
            packetQueue.Unlock();

            if(avPacket == nullptr){
                continue;
            }

            decoder.SendPacket(avPacket);
            while (1){
                EyerAVFrame * frame = new EyerAVFrame();
                int ret = decoder.RecvFrame(*frame);
                if(ret){
                    break;
                }
            }

            if(avPacket != nullptr){
                delete avPacket;
                avPacket = nullptr;
            }
        }

        EyerLog("EyerDecodeQueueFFmpeg Stop, Stream Id: %d\n", avStream.GetStreamId());
    }
}