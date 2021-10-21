#include "EyerDeocdeQueueFFmpeg.hpp"

namespace Eyer
{
    EyerDeocdeQueueFFmpeg::EyerDeocdeQueueFFmpeg(const EyerAVStream & stream, EyerConditionVariableBox * _cvBox)
        : EyerDeocdeQueue(stream, _cvBox)
    {

    }

    EyerDeocdeQueueFFmpeg::~EyerDeocdeQueueFFmpeg()
    {
        StopDecode();
        packetQueue.Lock();
        while(packetQueue.Size() > 0){
            EyerAVPacket * packet = packetQueue.FrontPop();
            if(packet != nullptr){
                delete packet;
                packet = nullptr;
            }
        }
        packetQueue.Unlock();
    }

    int EyerDeocdeQueueFFmpeg::StartDecode()
    {
        Start();
        return 0;
    }

    int EyerDeocdeQueueFFmpeg::StopDecode()
    {
        Stop();
        return 0;
    }

    void EyerDeocdeQueueFFmpeg::Run()
    {
        EyerLog("FFmpegDecodeThread Start\n");

        EyerAVDecoder decoder;
        int ret = decoder.Init(stream);
        if(ret){

        }

        while(!stopFlag){
            std::unique_lock<std::mutex> locker(cvBox->mtx);
            while(!stopFlag){
                // 查看 packet 缓存数据是否为 0
                if(packetQueue.SizeLock() > 0){
                    // 在看 Frame 缓存是否为 0
                    if(frameQueue.SizeLock() < 5){
                        break;
                    }
                }
                cvBox->cv.wait(locker);
            }

            if(frameQueue.SizeLock() >= 5){
                continue;
            }

            EyerAVPacket * packet = nullptr;

            // 尝试从缓存队列里取出来一个 Packet
            packetQueue.Lock();
            int size = packetQueue.Size();
            if(size > 0){
                packet = packetQueue.FrontPop();
                if(packet != nullptr){
                    packetQueueSize -= packet->GetSize();
                    if(packetQueueSize <= 0){
                        packetQueueSize = 0;
                    }
                    cvBox->cv.notify_all();
                }
            }
            packetQueue.Unlock();

            // 取失败了
            if(packet == nullptr){
                continue;
            }

            // 取成功了
            ret = decoder.SendPacket(packet);
            if(ret){
                continue;
            }
            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder.RecvFrame(*frame);
                if(ret){
                    break;
                }

                EyerLog("Frame PTS: %f\n", frame->GetSecPTS());
                frameQueue.PushLock(frame);

                /*
                if(frame != nullptr){
                    delete frame;
                    frame = nullptr;
                }
                */
            }

            if(packet != nullptr){
                delete packet;
                packet = nullptr;
            }
        }
        EyerLog("FFmpegDecodeThread Stop\n");
    }

    int EyerDeocdeQueueFFmpeg::SetStopFlag(){
        std::unique_lock<std::mutex> locker(cvBox->mtx);
        stopFlag = 1;
        cvBox->cv.notify_all();
        return 0;
    }
}
