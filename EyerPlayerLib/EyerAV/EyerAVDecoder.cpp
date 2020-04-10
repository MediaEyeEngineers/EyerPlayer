#include "EyerAV.hpp"

#include <QDebug>
#include "EyerAVStreamPrivate.hpp"
#include "EyerAVDecoderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

namespace Eyer
{
    EyerAVDecoder::EyerAVDecoder()
    {
        piml = new EyerAVDecoderPrivate();
        piml->codecContext = avcodec_alloc_context3(nullptr);
    }

    EyerAVDecoder::~EyerAVDecoder()
    {
        if(piml->codecContext != nullptr){
            avcodec_free_context(&piml->codecContext);
            piml->codecContext = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVDecoder::Init(EyerAVStream * stream)
    {
        avcodec_copy_context(piml->codecContext, stream->piml->codecContext);

        AVCodec * codec = avcodec_find_decoder(piml->codecContext->codec_id);

        piml->codecContext->thread_count = 4;

        int ret = avcodec_open2(piml->codecContext, codec, nullptr);
        if(ret){
            EyerLog("Open Decoder Fail\n");
            return -1;
        }

        // printf("NUM:%d\n", piml->codecContext->time_base.num);
        // printf("DEN:%d\n", piml->codecContext->time_base.den);

        return 0;
    }

    int EyerAVDecoder::GetFrameSize()
    {
        return piml->codecContext->frame_size;
    }

    int EyerAVDecoder::GetSampleRate()
    {
        return piml->codecContext->sample_rate;
    }

    int EyerAVDecoder::SendPacket(EyerAVPacket * packet)
    {
        // TODO 判断解码器是否打开
        AVPacket * avpkt = nullptr;
        if(packet != nullptr){
            avpkt = packet->piml->packet;
        }

        int ret = avcodec_send_packet(piml->codecContext, avpkt);
        return ret;
    }

    int EyerAVDecoder::RecvFrame(EyerAVFrame * frame)
    {
        // TODO 判断解码器是否打开
        int ret = avcodec_receive_frame(piml->codecContext, frame->piml->frame);
        qDebug() << "[CYL Debug] avcodec_receive_frame ret:" << ret;
        return ret;
    }
}
