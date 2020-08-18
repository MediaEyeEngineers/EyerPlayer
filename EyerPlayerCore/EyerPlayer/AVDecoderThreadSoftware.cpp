#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"

namespace EyerPlayer {
    AVDecoderThreadSoftware::AVDecoderThreadSoftware (Eyer::EyerAVStream & _stream, AVFrameQueueManager * _frameQueueManager)
            : AVDecoderThread(_stream, _frameQueueManager)
    {
    }

    AVDecoderThreadSoftware::~AVDecoderThreadSoftware()
    {

    }

    void AVDecoderThreadSoftware::Run()
    {
        EyerLog("AVDecoder Software Thread Start\n");

        decoder.Init(&stream);

        AVFrameQueue * frameQueue = nullptr;
        if (stream.GetStreamType() == Eyer::EyerAVStreamType::STREAM_TYPE_VIDEO) {
            frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_VIDEO, &frameQueue);
        } else if (stream.GetStreamType() == Eyer::EyerAVStreamType::STREAM_TYPE_AUDIO) {
            frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_AUDIO, &frameQueue);
        }

        Eyer::EyerAVRational timebase = stream.timebase;

        int ret = 0;
        while (!stopFlag) {
            Eyer::EyerTime::EyerSleepMilliseconds(1);

            if (frameQueue != nullptr) {
                if (frameQueue->Size() > 10) {
                    continue;
                }
            }

            Eyer::EyerAVPacket *pkt = nullptr;
            pktQueue.FrontPop(&pkt);
            if (pkt == nullptr) {
                continue;
            }

            if(pkt->IsLast()){
                if (pkt != nullptr) {
                    delete pkt;
                    pkt = nullptr;
                }
                break;
            }

            cacheSize -= pkt->GetSize();

            ret = decoder.SendPacket(pkt);
            if (ret) {
                continue;
            }
            while (1) {
                Eyer::EyerAVFrame * frame = new Eyer::EyerAVFrame();
                ret = decoder.RecvFrame(frame);

                if (ret) {
                    delete frame;
                    break;
                }

                if (frameQueue != nullptr) {
                    frameQueue->Push(frame);
                } else {
                    if (frame != nullptr) {
                        delete frame;
                        frame = nullptr;
                    }
                }


                double t = frame->GetPTS() * 1.0 * timebase.num / timebase.den;
                frame->timePts = t;
            }

            if (pkt != nullptr) {
                delete pkt;
                pkt = nullptr;
            }
        }


        ret = decoder.SendPacket(nullptr);
        while (1) {
            Eyer::EyerAVFrame *frame = new Eyer::EyerAVFrame();
            ret = decoder.RecvFrame(frame);

            if (ret) {
                delete frame;
                break;
            }

            if (frameQueue != nullptr) {
                frameQueue->Push(frame);
            } else {
                if (frame != nullptr) {
                    delete frame;
                    frame = nullptr;
                }
            }
            double t = frame->GetPTS() * 1.0 * timebase.num / timebase.den;
            frame->timePts = t;
        }

        EyerLog("AVDecoder Software Thread Stop\n");
    }
}