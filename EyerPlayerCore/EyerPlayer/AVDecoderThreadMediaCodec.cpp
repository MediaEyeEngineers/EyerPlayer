#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"

#include "EyerCodec/EyerCodec.hpp"

namespace Eyer {
    AVDecoderThreadMediaCodec::AVDecoderThreadMediaCodec(Eyer::EyerAVStream & _stream, AVFrameQueueManager * _frameQueueManager, jobject _surface)
            : AVDecoderThread(_stream, _frameQueueManager)
    {
        surface = _surface;
    }

    AVDecoderThreadMediaCodec::~AVDecoderThreadMediaCodec()
    {

    }

    void AVDecoderThreadMediaCodec::Run()
    {
        EyerLog("AVDecoder MediaCodec Thread Start\n");

        Eyer::EyerAVBitstreamFilter bitstreamFilter(Eyer::EyerAVBitstreamFilterType::h264_mp4toannexb, stream);

        frameQueueManager->GetMediaCodecQueueInit(stream, surface);
        Eyer::EyerMediaCodec * mediaCodec = nullptr;
        frameQueueManager->GetMediaCodecQueue(&mediaCodec);

        // 解码
        while (!stopFlag) {
            Eyer::EyerTime::EyerSleepMilliseconds(1);

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

            bitstreamFilter.SendPacket(pkt);
            while(!stopFlag){
                Eyer::EyerAVPacket annexbPkt;
                int ret = bitstreamFilter.ReceivePacket(&annexbPkt);
                if(ret){
                    break;
                }

                stream.ScalerPacketPTS(annexbPkt);

                while(!stopFlag) {
                    int index = mediaCodec->dequeueInputBuffer(1000 * 100);

                    if (index >= 0) {
                        mediaCodec->putInputData(index, annexbPkt.GetDataPtr(), annexbPkt.GetSize());
                        mediaCodec->queueInputBuffer(index, 0, annexbPkt.GetSize(), (double)(annexbPkt.GetSecPTS() * 1000.0), 0);

                        break;
                    }
                }
            }

            if (pkt != nullptr) {
                delete pkt;
                pkt = nullptr;
            }
        }

        Eyer::EyerJNIEnvManager::jvm->DetachCurrentThread();

        EyerLog("AVDecoder MediaCodec Thread Stop\n");
    }
}