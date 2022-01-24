#include "EyerDeocderQueueFFmpeg.hpp"

namespace Eyer
{
    EyerDeocderQueueFFmpeg::EyerDeocderQueueFFmpeg(const EyerAVStream & _stream, EyerConditionVariableBox * _cvBox)
        : EyerDeocderQueue(_stream, _cvBox)
    {

    }

    EyerDeocderQueueFFmpeg::~EyerDeocderQueueFFmpeg()
    {

    }

    int EyerDeocderQueueFFmpeg::StartDecode()
    {
        Start();
        return 0;
    }

    int EyerDeocderQueueFFmpeg::StopDecode()
    {
        Stop();
        return 0;
    }

    int EyerDeocderQueueFFmpeg::FlushDecoder()
    {
        return 0;
    }

    void EyerDeocderQueueFFmpeg::Run()
    {
        EyerLog("FFmpegDecodeThread Start, Stream Index: %d\n", stream.GetStreamId());

        EyerAVDecoder * decoder = new EyerAVDecoder();
        int ret = decoder->Init(stream);
        if(ret){
            EyerLog("FFmpeg decoder %d init fail: %d\n", stream.GetStreamId(), ret);
        }

        EyerAVPacket * packet = nullptr;

        while(!stopFlag){
            std::unique_lock<std::mutex> locker(cvBox->mtx);
            while (!stopFlag) {
                if(frameQueue.SizeLock() >= 5 || packetQueue.SizeLock() <= 0){
                    cvBox->cv.wait(locker);
                }
                else {
                    break;
                }
            }

            if(packet == nullptr) {
                packet = GetPacket();
                if(packet != nullptr){
                    cvBox->cv.notify_all();
                }
            }

            if(packet == nullptr){
                continue;
            }

            // 解码
            locker.unlock();

            decoder->SendPacket(packet);
            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder->RecvFrame(*frame);
                if(ret){
                    if(frame != nullptr){
                        delete frame;
                        frame = nullptr;
                    }
                    break;
                }

                // EyerLog("PTS: %f\n", frame->GetSecPTS());

                frameQueue.Lock();
                frameQueue.Push(frame);
                frameQueue.Unlock();
                cvBox->cv.notify_all();
                /*
                if(frame != nullptr){
                    delete frame;
                    frame = nullptr;
                }
                */
            }

            locker.lock();

            if(packet != nullptr){
                delete packet;
                packet = nullptr;
            }
        }

        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }
        EyerLog("FFmpegDecodeThread Stop\n");
    }

    int EyerDeocderQueueFFmpeg::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(cvBox->mtx);
        stopFlag = 1;
        cvBox->cv.notify_all();
        return 0;
    }

    int EyerDeocderQueueFFmpeg::SetStartEventLoopFlag()
    {
        std::unique_lock<std::mutex> locker(cvBox->mtx);
        eventLoopFlag = 1;
        cvBox->cv.notify_all();
        return 0;
    }
}