#include "EyerAVEncoder.hpp"

#include "EyerAVEncoderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

#include "EyerCore/EyerCore.hpp"

#include "EyerAVADTSUtil.hpp"

namespace Eyer {
    EyerAVEncoder::EyerAVEncoder() {
        piml = new EyerAVEncoderPrivate();
    }

    EyerAVEncoder::~EyerAVEncoder() {
        if (piml->codecContext != nullptr) {
            if (avcodec_is_open(piml->codecContext)) {
                avcodec_close(piml->codecContext);
            }
            avcodec_free_context(&piml->codecContext);
            piml->codecContext = nullptr;
        }

        if (piml != nullptr) {
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVEncoder::Init(const EyerAVEncoderParam &param) {
        AVCodec *codec = nullptr;
        if (param.codecId == CodecId::CODEC_ID_H264) {
            codec = avcodec_find_encoder(AV_CODEC_ID_H264);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
            piml->codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
            piml->codecContext->width = param.width;
            piml->codecContext->height = param.height;

            piml->codecContext->time_base.den = param.timebase.den;
            piml->codecContext->time_base.num = param.timebase.num;
        }

        if (param.codecId == CodecId::CODEC_ID_AAC) {
            codec = avcodec_find_encoder(AV_CODEC_ID_AAC);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = AV_SAMPLE_FMT_FLTP;

            piml->codecContext->sample_rate = param.sample_rate;

            piml->codecContext->channel_layout = AV_CH_LAYOUT_STEREO;
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);

            piml->codecContext->time_base.den = param.sample_rate;
            piml->codecContext->time_base.num = 1;
        }


        if (param.codecId == CodecId::CODEC_ID_MP3) {
            codec = avcodec_find_encoder(AV_CODEC_ID_MP3);

            if (piml->codecContext != nullptr) {
                if (avcodec_is_open(piml->codecContext)) {
                    avcodec_close(piml->codecContext);
                }
                avcodec_free_context(&piml->codecContext);
                piml->codecContext = nullptr;

                return -1;
            }

            piml->codecContext = avcodec_alloc_context3(codec);

            piml->codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
            piml->codecContext->sample_fmt = AV_SAMPLE_FMT_FLTP;

            piml->codecContext->sample_rate = param.sample_rate;

            piml->codecContext->channel_layout = AV_CH_LAYOUT_STEREO;
            piml->codecContext->channels = av_get_channel_layout_nb_channels(piml->codecContext->channel_layout);
        }

        int ret = avcodec_open2(piml->codecContext, codec, nullptr);

        return ret;
    }

    int EyerAVEncoder::GetFrameSize()
    {
        return piml->codecContext->frame_size;
    }

    int EyerAVEncoder::SendFrame(EyerAVFrame &frame) {
        return avcodec_send_frame(piml->codecContext, frame.piml->frame);
    }

    int EyerAVEncoder::SendFrameNull() {
        return avcodec_send_frame(piml->codecContext, nullptr);
    }

    int EyerAVEncoder::RecvPacket(EyerAVPacket &packet) {
        return avcodec_receive_packet(piml->codecContext, packet.piml->packet);
    }

    int EyerAVEncoder::GetTimebase(EyerAVRational &timebase) {
        timebase.num = piml->codecContext->time_base.num;
        timebase.den = piml->codecContext->time_base.den;
        return 0;
    }

    EyerAVRational EyerAVEncoder::GetTimebase()
    {
        EyerAVRational timebase;
        GetTimebase(timebase);
        return timebase;
    }

    EyerAVADTS EyerAVEncoder::GetADTS(int packetSize)
    {
        EyerAVADTSUtil adtsUtil;
        EyerAVADTS avadts = adtsUtil.GetADTS(piml->codecContext->extradata, piml->codecContext->extradata_size, packetSize);

        return avadts;
    }
}
