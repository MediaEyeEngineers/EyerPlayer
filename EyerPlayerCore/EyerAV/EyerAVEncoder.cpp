#include "EyerAVAV.hpp"

#include "EyerAVStreamPrivate.hpp"
#include "EyerAVDecoderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVFramePrivate.hpp"
#include "EyerAVEncoderPrivate.hpp"

namespace Eyer
{
    EyerAVEncoder::EyerAVEncoder()
    {
        // av_register_all();
        avformat_network_init();
        piml = new EyerAVEncoderPrivate();
    }

    EyerAVEncoder::~EyerAVEncoder()
    {
        if(piml->codecContext != nullptr){
            if(avcodec_is_open(piml->codecContext)){
                avcodec_close(piml->codecContext);
            }
            avcodec_free_context(&piml->codecContext);
            piml->codecContext = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVEncoder::GetTimeBase(EyerAVRational & rational)
    {
        rational.num = piml->codecContext->time_base.num;
        rational.den = piml->codecContext->time_base.den;
        return 0;
    }

    int EyerAVEncoder::Init(EncoderParam * param)
    {
        AVCodec * codec = nullptr;
        if(param->codecId == CodecId::CODEC_ID_H264){
            // 初始化 H264 编码器
            codec = avcodec_find_encoder(AV_CODEC_ID_H264);

            if(piml->codecContext != nullptr){
                if(avcodec_is_open(piml->codecContext)){
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->time_base.den = param->fps;
            piml->codecContext->time_base.num = 1;

            piml->codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            piml->codecContext->pix_fmt = AV_PIX_FMT_YUVJ420P;
            piml->codecContext->width = param->width;
            piml->codecContext->height = param->height;

            piml->codecContext->thread_count = 4;

            piml->codecContext->me_range = 16;
            piml->codecContext->max_qdiff = 4;
            piml->codecContext->qmin = 10;
            piml->codecContext->qmax = 51;
            piml->codecContext->qcompress = 0.8;
            piml->codecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
        }

        if(param->codecId == CodecId::CODEC_ID_AAC){
            // 初始化 AAC 编码器
            codec = avcodec_find_encoder(AV_CODEC_ID_AAC);
            if(codec == nullptr){
                printf("avcodec_find_encoder(AV_CODEC_ID_AAC) Fail\n");
            }
            else{
                // printf("avcodec_find_encoder(AV_CODEC_ID_AAC) Success\n");
            }

            if(piml->codecContext != nullptr){
                if(avcodec_is_open(piml->codecContext)){
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->time_base.den = 44100;
            piml->codecContext->time_base.num = 1;

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = AV_SAMPLE_FMT_FLTP;
            // piml->codecContext->sample_fmt = AV_SAMPLE_FMT_S16;

            piml->codecContext->sample_rate = 44100;

            piml->codecContext->channel_layout = AV_CH_LAYOUT_STEREO;
            // piml->codecContext->channel_layout = AV_CH_LAYOUT_MONO;
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);

            // piml->codecContext->bit_rate = 8192;
        }

        int ret = avcodec_open2(piml->codecContext, codec, nullptr);
        if(ret){
            EyerLog("Open Decoder Fail\n");
            return -1;
        }

        // printf("Frame Size:%d\n", piml->codecContext->frame_size);

        return 0;
    }

    int EyerAVEncoder::GetBufferSize()
    {
        int size = av_samples_get_buffer_size(NULL, piml->codecContext->channels,piml->codecContext->frame_size,piml->codecContext->sample_fmt, 1);
        return size;
    }

    int EyerAVEncoder::_Init(EyerAVStream * stream)
    {
        AVCodec * codec = nullptr;

        EyerAVStreamType streamType = stream->GetStreamType();
        if(streamType == EyerAVStreamType::STREAM_TYPE_UNKNOW){
        }
        if(streamType == EyerAVStreamType::STREAM_TYPE_AUDIO){
            // 初始化 AAC 编码器
            codec = avcodec_find_encoder(AV_CODEC_ID_AAC);

            if(piml->codecContext != nullptr){
                if(avcodec_is_open(piml->codecContext)){
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            avcodec_parameters_to_context(piml->codecContext, stream->piml->codecpar);
        }
        if(streamType == EyerAVStreamType::STREAM_TYPE_VIDEO){
            // 初始化 H264 编码器
            codec = avcodec_find_encoder(AV_CODEC_ID_H264);

            if(piml->codecContext != nullptr){
                if(avcodec_is_open(piml->codecContext)){
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            avcodec_parameters_to_context(piml->codecContext, stream->piml->codecpar);
            /*
            piml->codecContext->time_base.den = 90000;
            piml->codecContext->time_base.num = 1;

            piml->codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
            piml->codecContext->width = stream->piml->codecContext->width;
            piml->codecContext->height = stream->piml->codecContext->height;
            */

            piml->codecContext->me_range = 16;
            piml->codecContext->max_qdiff = 4;
            piml->codecContext->qmin = 10;
            piml->codecContext->qmax = 51;
            piml->codecContext->qcompress = 0.8;
            piml->codecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
        }

        if(codec == nullptr){
            return -1;
        }
        if(piml->codecContext == nullptr){
            return -1;
        }

        int ret = avcodec_open2(piml->codecContext, codec, nullptr);
        if(ret){
            EyerLog("Open Decoder Fail\n");
            return -1;
        }
        
        return 0;
    }

    int EyerAVEncoder::SendFrame(EyerAVFrame * frame)
    {
        if(piml->codecContext == nullptr){
            return -1;
        }

        AVFrame * f = NULL;
        if(frame != nullptr){
            f = frame->piml->frame;
        }
        int ret = avcodec_send_frame(piml->codecContext, f);
        return ret;
    }

    int EyerAVEncoder::RecvPacket(EyerAVPacket * packet)
    {
        if(piml->codecContext == nullptr){
            return -1;
        }

        int ret = avcodec_receive_packet(piml->codecContext, packet->piml->packet);
        return ret;
    }

    int EyerAVEncoder::GetFrameSize()
    {
        return piml->codecContext->frame_size;
    }

    int EyerAVEncoder::GetChannelNum()
    {
        return piml->codecContext->channels;
    }

    int EyerAVEncoder::Flush()
    {
        avcodec_flush_buffers(piml->codecContext);
        return 0;
    }

    int EyerAVEncoder::GetFPS()
    {
        return piml->codecContext->time_base.den;
    }
}
