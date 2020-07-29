#include "EyerAVAV.hpp"

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

#ifdef EYER_HW_DECODER
    static bool IsSupportHW(AVCodec * codec, AVHWDeviceType type)
    {
        for (int i = 0; ; i++) {
            const AVCodecHWConfig * config = avcodec_get_hw_config(codec, i);
            if (!config) {
                break;
            }

            if (config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX && config->device_type == type) {
                // hw_pix_fmt = config->pix_fmt; //获取硬件支持的图像格式
                return true;
            }
        }
        return false;
    }
#endif

    int EyerAVDecoder::InitHW(EyerAVStream * stream)
    {
        avcodec_parameters_to_context(piml->codecContext, stream->piml->codecpar);
        AVCodec * codec = avcodec_find_decoder(piml->codecContext->codec_id);

#ifdef EYER_HW_DECODER

        if(codec->id == AVCodecID::AV_CODEC_ID_H264){
            Eyer::EyerString hwList[] = {"dxva2"};

            int size = sizeof(hwList) / sizeof(Eyer::EyerString);

            for(int hwIndex = 0; hwIndex < size; hwIndex++){
                enum AVHWDeviceType type = av_hwdevice_find_type_by_name(hwList[hwIndex].str);
                if(type == AVHWDeviceType::AV_HWDEVICE_TYPE_NONE){
                    continue;
                }

                bool support = IsSupportHW(codec, type);
                if(!support){
                    continue;
                }

                int err;
                AVBufferRef *hw_device_ctx = NULL;
                if ((err = av_hwdevice_ctx_create(&hw_device_ctx, type, NULL, NULL, 0)) < 0) {
                    continue;
                }

                piml->codecContext->hw_device_ctx = hw_device_ctx;
                piml->isHW = 1;
                break;
            }
        }

#endif

        int ret = avcodec_open2(piml->codecContext, codec, nullptr);
        if(ret){
            EyerLog("Open Decoder Fail\n");
            return -1;
        }

        return 0;
    }

    int EyerAVDecoder::Init(EyerAVStream * stream)
    {
        avcodec_parameters_to_context(piml->codecContext, stream->piml->codecpar);

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
#ifdef EYER_HW_DECODER
        int ret;
        if(piml->isHW){
            EyerAVFrame f;
            ret = avcodec_receive_frame(piml->codecContext, f.piml->frame);
            if(!ret){
                av_hwframe_transfer_data(frame->piml->frame, f.piml->frame, 0);
                frame->piml->frame->pts = f.piml->frame->pts;
            }
        }
        else{
            ret = avcodec_receive_frame(piml->codecContext, frame->piml->frame);
        }

        return ret;
#else
        int ret = avcodec_receive_frame(piml->codecContext, frame->piml->frame);
        return ret;
#endif
    }
}
