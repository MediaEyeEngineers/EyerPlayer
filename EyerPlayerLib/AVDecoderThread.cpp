#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "PlayerEvent.hpp"
#include <QDebug>

extern "C"{
#include <libavutil/common.h>
#include <libavutil/error.h>
}

namespace EyerPlayer {
    AVDecoderThread::AVDecoderThread(Eyer::EyerAVStream & stream, StreamInfo & _streamInfo,Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _queueManager)
    {
        streamInfo = _streamInfo;

        queueManager = _queueManager;
        eventQueue = _eventQueue;
        decoder = new Eyer::EyerAVDecoder();
        decoder->Init(&stream);

        streamId = stream.streamIndex;

        isReadFinish = 0;
    }

    AVDecoderThread::~AVDecoderThread()
    {
        while(pktQueue.Size() > 0){
            Eyer::EyerAVPacket * pkt = nullptr;
            pktQueue.FrontPop(&pkt);
            if(pkt != nullptr){
                delete pkt;
            }
        }

        Eyer::EyerString queueKey = Eyer::EyerString(EventTag::FRAME_QUEUE_DECODER_VIDEO) + Eyer::EyerString::Number(streamId);

        AVFrameQueue * decoderQueue = nullptr;
        queueManager->GetQueue(queueKey, &decoderQueue);
        if(decoderQueue != nullptr){
            while(decoderQueue->Size() > 0){
                Eyer::EyerAVFrame * f = nullptr;
                decoderQueue->FrontPop(&f);
                if(f != nullptr){
                    delete f;
                }
            }
        }

        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }
    }

    int AVDecoderThread::SetReadFinishFlag()
    {
        isReadFinish = 1;
        return 0;
    }

    int AVDecoderThread::PushPkt(Eyer::EyerAVPacket * pkt)
    {
        if(pkt->GetStreamId() != streamId){
            return -1;
        }

        pktQueue.Push(pkt);
        return 0;
    }

    int AVDecoderThread::GetQueueSize()
    {
        return pktQueue.Size();
    }

    int AVDecoderThread::GetFrameQueueSize()
    {
        Eyer::EyerString queueKey = Eyer::EyerString(EventTag::FRAME_QUEUE_DECODER_VIDEO) + Eyer::EyerString::Number(streamId);

        AVFrameQueue * decoderQueue = nullptr;
        queueManager->GetQueue(queueKey, &decoderQueue);
        if(decoderQueue == nullptr){
            return 0;
        }

        return decoderQueue->Size();
    }

    int AVDecoderThread::GetStreamId()
    {
        return streamId;
    }

    int AVDecoderThread::HasNewFrame()
    {
        return 0;
    }

    void AVDecoderThread::Run()
    {
        SetRunning();

        qDebug() << "Stream Id: " << streamId << " Decoder Thread Start" << endl;

        Eyer::EyerString queueKey = Eyer::EyerString(EventTag::FRAME_QUEUE_DECODER_VIDEO) + Eyer::EyerString::Number(streamId);

        AVFrameQueue * decoderQueue = nullptr;
        queueManager->GetQueue(queueKey, &decoderQueue);
        if(decoderQueue == nullptr){
            qDebug() << "Decoder Thread Get Frame Queue Fail" << endl;
        }

        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            if(isReadFinish){
                // Read 线程已经读取完毕了，如果 这时候所有的 packet 用完了，那么可以退出主循环，进行末尾解码
                if(pktQueue.Size() <= 0){
                    break;
                }
            }

            if(decoderQueue->Size() >= 5){
                // qDebug() << "Stream Id: " << streamId << " Decoder Thread Block!!" << endl;
                continue;
            }

            Eyer::EyerAVPacket * pkt = nullptr;
            pktQueue.FrontPop(&pkt);
            if(pkt != nullptr){
                int ret = decoder->SendPacket(pkt);
                qDebug() << "[CYL Debug decoder->SendPacket] ret:" << ret << endl;
                if(ret) {
                    qDebug() << "[CYL Debug decoder->SendPacket] ret is AVERROR(EAGAIN)" << endl;
                    // continue;
                }

                while(ret >= 0) {
                    Eyer::EyerAVFrame * frame = new Eyer::EyerAVFrame();
                    ret = decoder->RecvFrame(frame);

                    if (ret == AVERROR(EAGAIN)  || AVERROR_EOF == ret) {
                        qDebug() << "[CYL Debug decoder->RecvFrame] ret == AVERROR(EAGAIN)" << ret << endl;
                        delete frame;
                        break;
                    }
                    double t = frame->GetPTS() * 1.0 * streamInfo.timeBaseNum / streamInfo.timeBaseDen;
                    frame->timePts = t;
                    qDebug() << "timePts:" << t << endl;
                    decoderQueue->Push(frame);
                    //delete frame;
                }
            }
            if(pkt != nullptr){
                delete pkt;
            }
        }

//        int ret = decoder->SendPacket(nullptr);
//        while(!stopFlag){
//            Eyer::EyerTime::EyerSleep(1000);

//            if(decoderQueue->Size() >= 5){
//                continue;
//            }

//            Eyer::EyerAVFrame * frame = new Eyer::EyerAVFrame();
//            ret = decoder->RecvFrame(frame);

//            if(ret){
//                delete frame;
//                break;
//            }

//            double t = frame->GetPTS() * 1.0 * streamInfo.timeBaseNum / streamInfo.timeBaseDen;
//            frame->timePts = t;

//            decoderQueue->Push(frame);
//        }

        qDebug() << "Decoder Thread Stop " << streamId << endl;

        SetStoping();
    }
}
