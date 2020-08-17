#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"

#include "EyerCodec/EyerCodec.hpp"

namespace EyerPlayer {
    AVDecoderThreadMediaCodec::AVDecoderThreadMediaCodec(Eyer::EyerAVStream & _stream, AVFrameQueueManager * _frameQueueManager)
            : AVDecoderThread(_stream, _frameQueueManager)
    {

    }

    AVDecoderThreadMediaCodec::~AVDecoderThreadMediaCodec()
    {

    }

    void AVDecoderThreadMediaCodec::Run()
    {
        EyerLog("AVDecoder MediaCodec Thread Start\n");

        AVFrameQueue * frameQueue = nullptr;
        if (stream.GetStreamType() == Eyer::EyerAVStreamType::STREAM_TYPE_VIDEO) {
            frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_VIDEO, &frameQueue);
        } else if (stream.GetStreamType() == Eyer::EyerAVStreamType::STREAM_TYPE_AUDIO) {
            frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_AUDIO, &frameQueue);
        }

        Eyer::EyerMediaCodec mediaCodec;
        mediaCodec.BindDecoderThread();
        mediaCodec.BindPlayCtrThread();

        mediaCodec.Init(stream);
        // 解码
        while (!stopFlag) {
            Eyer::EyerAVPacket * pkt = nullptr;
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

            mediaCodec.SendPacket(pkt);

            while(1){
                int ret = mediaCodec.RecvFrameRender();
                if(ret){
                    break;
                }
            }

            if (pkt != nullptr) {
                delete pkt;
                pkt = nullptr;
            }
        }

        EyerLog("AVDecoder MediaCodec Thread Stop\n");
    }
}