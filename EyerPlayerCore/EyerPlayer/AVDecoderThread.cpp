#include "EyerPlayerThread.hpp"

namespace EyerPlayer {
    AVDecoderThread::AVDecoderThread(Eyer::EyerAVStream * stream)
    {
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

        int ret = 0;
        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

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

                // EyerLog("frame: %lld\n", frame->GetPTS());

                if(frame != nullptr){
                    delete frame;
                    frame = nullptr;
                }

                // double t = frame->GetPTS() * 1.0 * streamInfo.timeBaseNum / streamInfo.timeBaseDen;
                // frame->timePts = t;
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

            if(frame != nullptr){
                delete frame;
                frame = nullptr;
            }

            // double t = frame->GetPTS() * 1.0 * streamInfo.timeBaseNum / streamInfo.timeBaseDen;
            // frame->timePts = t;
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
            cacheSize < 0;
        }
        return cacheSize;
    }
}