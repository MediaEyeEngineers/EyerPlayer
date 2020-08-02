#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"

namespace EyerPlayer {
    AVDecoderThread::AVDecoderThread(Eyer::EyerAVStream * stream, Eyer::EyerAVRational _timebase,Eyer::EyerAVStreamType _streamType, AVFrameQueueManager * _frameQueueManager)
    {
        timebase = _timebase;
        streamType = _streamType;
        frameQueueManager = _frameQueueManager;

        int ret = decoder.Init(stream);
        if(ret){
            EyerLog("AVDecoderThread Init\n");
        }
    }

    AVDecoderThread::~AVDecoderThread()
    {

    }

    void AVDecoderThread::Run()
    {
        EyerLog("AVDecoder Thread Start\n");

        AVFrameQueue * frameQueue = nullptr;
        if(streamType == Eyer::EyerAVStreamType::STREAM_TYPE_VIDEO){
            frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_VIDEO, &frameQueue);
        }
        else if(streamType == Eyer::EyerAVStreamType::STREAM_TYPE_AUDIO){
            frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_AUDIO, &frameQueue);
        }

        int ret = 0;
        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);

            if(frameQueue != nullptr){
                if(frameQueue->Size() > 10){
                    continue;
                }
            }

            Eyer::EyerAVPacket * pkt = nullptr;
            pktQueue.FrontPop(&pkt);
            if(pkt == nullptr){
                continue;
            }
            cacheSize -= pkt->GetSize();

            ret = decoder.SendPacket(pkt);
            if(ret){
                continue;
            }
            while(1){
                Eyer::EyerAVFrame * frame = new Eyer::EyerAVFrame();
                ret = decoder.RecvFrame(frame);

                if(ret){
                    delete frame;
                    break;
                }

                if(frameQueue != nullptr){
                    frameQueue->Push(frame);
                }
                else{
                    if(frame != nullptr){
                        delete frame;
                        frame = nullptr;
                    }
                }

                double t = frame->GetPTS() * 1.0 * timebase.num / timebase.den;
                frame->timePts = t;
            }

            if(pkt != nullptr){
                delete pkt;
                pkt = nullptr;
            }
        }


        ret = decoder.SendPacket(nullptr);
        while(1){
            Eyer::EyerAVFrame * frame = new Eyer::EyerAVFrame();
            ret = decoder.RecvFrame(frame);

            if(ret){
                delete frame;
                break;
            }

            if(frameQueue != nullptr){
                frameQueue->Push(frame);
            }
            else{
                if(frame != nullptr){
                    delete frame;
                    frame = nullptr;
                }
            }
            double t = frame->GetPTS() * 1.0 * timebase.num / timebase.den;
            frame->timePts = t;
        }

        EyerLog("AVDecoder Thread Stop\n");
    }

    int AVDecoderThread::SendPacket(Eyer::EyerAVPacket * pkt)
    {
        pktQueue.Push(pkt);
        cacheSize += pkt->GetSize();
        return 0;
    }

    int AVDecoderThread::GetPacketCount()
    {
        return pktQueue.Size();
    }

    int AVDecoderThread::GetPacketSize()
    {
        if(cacheSize < 0){
            cacheSize = 0;
        }
        return cacheSize;
    }
}