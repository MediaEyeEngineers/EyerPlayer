#include "EyerAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/imgutils.h>
}

#include "EyerAVEncoderPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

namespace Eyer {
    EyerAVFrame::EyerAVFrame() {
        piml = new EyerAVFramePrivate();
        piml->frame = av_frame_alloc();
    }

    EyerAVFrame::~EyerAVFrame() {
        av_frame_unref(piml->frame);
        av_frame_free(&piml->frame);
        if (piml != nullptr) {
            delete piml;
            piml = nullptr;
        }

        for(int i=0;i<dataManager.size();i++){
            free(dataManager[i]);
        }
        dataManager.clear();
    }

    EyerAVFrame::EyerAVFrame(const EyerAVFrame & frame)
    {
        piml = new EyerAVFramePrivate();
        piml->frame = av_frame_alloc();
        *this = frame;
    }
    EyerAVFrame & EyerAVFrame::operator = (const EyerAVFrame & frame)
    {
        // Copy data
        // YUV 420 Data
        int width                           = frame.piml->frame->width;
        int height                          = frame.piml->frame->height;

        // Copy width ,height
        piml->frame->width                  = frame.piml->frame->width;
        piml->frame->height                 = frame.piml->frame->height;

        piml->frame->channels               = frame.piml->frame->channels;
        piml->frame->channel_layout         = frame.piml->frame->channel_layout;
        piml->frame->nb_samples             = frame.piml->frame->nb_samples;
        piml->frame->format                 = frame.piml->frame->format;
        piml->frame->key_frame              = frame.piml->frame->key_frame;
        piml->frame->pict_type              = frame.piml->frame->pict_type;
        piml->frame->sample_aspect_ratio    = frame.piml->frame->sample_aspect_ratio;
        piml->frame->pts                    = frame.piml->frame->pts;
        piml->frame->pkt_dts                = frame.piml->frame->pkt_dts;
        piml->frame->coded_picture_number   = frame.piml->frame->coded_picture_number;
        piml->frame->display_picture_number = frame.piml->frame->display_picture_number;
        piml->frame->quality                = frame.piml->frame->quality;

        // Copy linesize
        for(int i=0;i<AV_NUM_DATA_POINTERS;i++){
            piml->frame->linesize[i] = frame.piml->frame->linesize[i];
        }

        if(frame.GetPixFormat() < 200 && frame.GetPixFormat() >= 100){
            // 图像
            {
                int linesizeIndex = 0;
                int h = height;
                if(frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
                    h = height;
                }
                if(frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P || frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.piml->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.piml->frame->data[linesizeIndex], dataLen);

                piml->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
            {
                int linesizeIndex = 1;
                int h = height;
                if(frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
                    h = height / 2;
                }
                if(frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P || frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.piml->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.piml->frame->data[linesizeIndex], dataLen);

                piml->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
            {
                int linesizeIndex = 2;
                int h = height;
                if(frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
                    h = height / 2;
                }
                if(frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P || frame.GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.piml->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.piml->frame->data[linesizeIndex], dataLen);

                piml->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
        }

        {
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLTP){
                int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)piml->frame->format);
                int channelSize = piml->frame->nb_samples * sizePerSample;

                for(int channelIndex=0; channelIndex<piml->frame->channels; channelIndex++){
                    unsigned char * data = (unsigned char *)malloc(channelSize);
                    memcpy(data, frame.piml->frame->data[channelIndex], channelSize);
                    piml->frame->data[channelIndex] = data;
                    dataManager.push_back(data);
                }
            }
        }

        

        // Copy extended_data




        return *this;
    }

    int EyerAVFrame::GetYData(unsigned char * yData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int h = height;
        int w = width;

        if(GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
            h = height;
            w = width;
        }
        if(GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P || GetPixFormat() ==  EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(yData + offset, piml->frame->data[0] + i * piml->frame->linesize[0], w);
            offset += w;
        }

        return 0;
    }

    int EyerAVFrame::GetUData(unsigned char * uData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int h = height;
        int w = width;

        if(GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
            h = height / 2;
            w = width / 2;
        }
        if(GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P || GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(uData + offset, piml->frame->data[1] + i * piml->frame->linesize[1], w);
            offset += w;
        }

        return 0;
    }

    int EyerAVFrame::GetVData(unsigned char * vData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int h = height;
        int w = width;

        if(GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
            h = height / 2;
            w = width / 2;
        }
        if(GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P || GetPixFormat() == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(vData + offset, piml->frame->data[2] + i * piml->frame->linesize[2], w);
            offset += w;
        }
        return 0;
    }

    int EyerAVFrame::SetPTS(int64_t pts)
    {
        piml->frame->pts = pts;
        return 0;
    }

    int EyerAVFrame::GetLineSize(int channel) {
        return piml->frame->linesize[channel];
    }

    int EyerAVFrame::GetWidth() {
        return piml->frame->width;
    }

    int EyerAVFrame::GetHeight() {
        return piml->frame->height;
    }

    int64_t EyerAVFrame::GetPTS()
    {
        return piml->frame->pts;
    }

    int EyerAVFrame::GetInfo() {
        printf("===============================================================\n");

        for(int i=0;i<AV_NUM_DATA_POINTERS;i++) {
            printf("Linesize [%d]: %d\n", i, piml->frame->linesize[i]);
        }
        
        printf("Width: %d\n", piml->frame->width);
        printf("Height: %d\n", piml->frame->height);
        printf("Channels: %d\n", piml->frame->channels);
        printf("channel_layout: %d\n", piml->frame->channel_layout);
        printf("nb_samples: %d\n", piml->frame->nb_samples);
        printf("format: %d\n", piml->frame->format);

        int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)piml->frame->format);
        printf("Size Per Sample: %d\n", sizePerSample);

        {
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_RGB){
                printf("AVColorSpace: AVCOL_SPC_RGB\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_BT709){
                printf("AVColorSpace: AVCOL_SPC_BT709\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_UNSPECIFIED){
                printf("AVColorSpace: AVCOL_SPC_UNSPECIFIED\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_RESERVED){
                printf("AVColorSpace: AVCOL_SPC_RESERVED\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_FCC){
                printf("AVColorSpace: AVCOL_SPC_FCC\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_BT470BG){
                printf("AVColorSpace: AVCOL_SPC_BT470BG\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_SMPTE170M){
                printf("AVColorSpace: AVCOL_SPC_SMPTE170M\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_SMPTE240M){
                printf("AVColorSpace: AVCOL_SPC_SMPTE240M\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_YCGCO){
                printf("AVColorSpace: AVCOL_SPC_YCGCO\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_YCOCG){
                printf("AVColorSpace: AVCOL_SPC_YCOCG\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_BT2020_NCL){
                printf("AVColorSpace: AVCOL_SPC_BT2020_NCL\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_BT2020_CL){
                printf("AVColorSpace: AVCOL_SPC_BT2020_CL\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_SMPTE2085){
                printf("AVColorSpace: AVCOL_SPC_SMPTE2085\n");
            }
            /*
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_CHROMA_DERIVED_NCL){
                printf("AVColorSpace: AVCOL_SPC_CHROMA_DERIVED_NCL\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_CHROMA_DERIVED_CL){
                printf("AVColorSpace: AVCOL_SPC_CHROMA_DERIVED_CL\n");
            }
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_ICTCP){
                printf("AVColorSpace: AVCOL_SPC_ICTCP\n");
            }
            */
            if(piml->frame->colorspace == AVColorSpace::AVCOL_SPC_NB){
                printf("AVColorSpace: AVCOL_SPC_NB\n");
            }
        }

        {
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUV420P){
                printf("Format: AV_PIX_FMT_YUV420P\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ420P){
                printf("Format: AV_PIX_FMT_YUVJ420P\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ422P){
                printf("Format: AV_PIX_FMT_YUVJ422P\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_RGB24){
                printf("Format: AV_PIX_FMT_RGB24\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_BGR24){
                printf("Format: AV_PIX_FMT_BGR24\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ444P){
                printf("Format: AV_PIX_FMT_YUVJ444P\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUV444P){
                printf("Format: AV_PIX_FMT_YUV444P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_NONE){
                printf("Format: AV_SAMPLE_FMT_NONE\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8){
                printf("Format: AV_SAMPLE_FMT_U8\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16){
                printf("Format: AV_SAMPLE_FMT_S16\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32){
                printf("Format: AV_SAMPLE_FMT_S32\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLT){
                printf("Format: AV_SAMPLE_FMT_FLT\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_DBL){
                printf("Format: AV_SAMPLE_FMT_DBL\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8P){
                printf("Format: AV_SAMPLE_FMT_U8P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16P){
                printf("Format: AV_SAMPLE_FMT_S16P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32P){
                printf("Format: AV_SAMPLE_FMT_S32P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLTP){
                printf("Format: AV_SAMPLE_FMT_FLTP\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_DBLP){
                printf("Format: AV_SAMPLE_FMT_DBLP\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S64){
                printf("Format: AV_SAMPLE_FMT_S64\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S64P){
                printf("Format: AV_SAMPLE_FMT_S64P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_NB){
                printf("Format: AV_SAMPLE_FMT_NB\n");
            }
        }

        {
        }

        // Print Channel Layout
        {
            if(piml->frame->channel_layout == AV_CH_LAYOUT_MONO){
                printf("Channel Layout: AV_CH_LAYOUT_MONO\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_STEREO){
                printf("Channel Layout: AV_CH_LAYOUT_STEREO\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_2POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_2POINT1\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_SURROUND){
                printf("Channel Layout: AV_CH_LAYOUT_SURROUND\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_2_1){
                printf("Channel Layout: AV_CH_LAYOUT_2_1\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_4POINT0){
                printf("Channel Layout: AV_CH_LAYOUT_4POINT0\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_3POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_3POINT1\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_5POINT0_BACK){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT0_BACK\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_5POINT0){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT0\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_5POINT1_BACK){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT1_BACK\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_5POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT1\n");
            }
        }
        
        return 0;
    }

    EyerAVAudioDateType EyerAVFrame::GetAudioDateType()
    {
        if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8){
            return EyerAVAudioDateType::UNSIGNEDINT;
        }
        if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8P){
            return EyerAVAudioDateType::UNSIGNEDINT;
        }



        if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16){
            return EyerAVAudioDateType::SIGNEDINT;
        }
        if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16P){
            return EyerAVAudioDateType::SIGNEDINT;
        }

        if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32){
            return EyerAVAudioDateType::UNSIGNEDINT;
        }
        if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32P){
            return EyerAVAudioDateType::UNSIGNEDINT;
        }



        if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLT){
            return EyerAVAudioDateType::FLOAT;
        }
        if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLTP){
            return EyerAVAudioDateType::FLOAT;
        }

        return EyerAVAudioDateType::UNSIGNEDINT;
    }

    EyerAVPixelFormat EyerAVFrame::GetPixFormat() const {
        if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUV420P){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P;
        }
        if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ420P){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P;
        }
        if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUV444P){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P;
        }
        if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ444P){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ444P;
        }

        return EyerAVPixelFormat::Eyer_AV_PIX_FMT_UNKNOW;
    }

    int EyerAVFrame::GetAudioPackedData(unsigned char * data)
    {
        int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)piml->frame->format);
        int bufferSize = sizePerSample * piml->frame->nb_samples * piml->frame->channels;
        if(data == nullptr){
            return bufferSize;
        }

        // 判断是 Packed 还是 Plane
        int isPanar = av_sample_fmt_is_planar((AVSampleFormat)piml->frame->format);
        if(isPanar){
            // EyerLog("Panar\n");
            SwrContext * swrCtx = swr_alloc_set_opts(
                        NULL,
                        piml->frame->channel_layout,
                        av_get_packed_sample_fmt((AVSampleFormat)piml->frame->format),
                        piml->frame->sample_rate,

                        piml->frame->channel_layout,
                        (AVSampleFormat)piml->frame->format,
                        piml->frame->sample_rate,

                        0,
                        NULL
                        );


            swr_init(swrCtx);

            int ret = swr_convert(swrCtx, &data, piml->frame->nb_samples, (const uint8_t **)piml->frame->data, piml->frame->nb_samples);

            swr_free(&swrCtx);
        }
        else{
            // EyerLog("Packed\n");
            memcpy(data, piml->frame->data[0], bufferSize);
        }

        return 0;
    }

    int EyerAVFrame::SetVideoData420P(unsigned char * _y, unsigned char * _u, unsigned char * _v, int _width, int _height)
    {
        unsigned char * y = (unsigned char *)malloc(_width * _height);
        memcpy(y, _y, _width * _height);

        unsigned char * u = (unsigned char *)malloc(_width * _height / 4);
        memcpy(u, _u, _width * _height / 4);

        unsigned char * v = (unsigned char *)malloc(_width * _height / 4);
        memcpy(v, _v, _width * _height / 4);

        dataManager.push_back(y);
        dataManager.push_back(u);
        dataManager.push_back(v);

        piml->frame->format = AV_PIX_FMT_YUV420P;
        piml->frame->width = _width;
        piml->frame->height = _height;

        piml->frame->linesize[0] = _width;
        piml->frame->linesize[1] = _width / 2;
        piml->frame->linesize[2] = _width / 2;

        piml->frame->data[0] = y;
        piml->frame->data[1] = u;
        piml->frame->data[2] = v;

        /*
        int ret = av_image_alloc(piml->frame->data, piml->frame->linesize, _width, _height, AV_PIX_FMT_YUV420P, 16);

        EyerLog("=====================================\n");
        EyerLog("linesize[0]:%d\n", piml->frame->linesize[0]);
        EyerLog("linesize[1]:%d\n", piml->frame->linesize[1]);
        EyerLog("linesize[2]:%d\n", piml->frame->linesize[2]);

        memcpy(piml->frame->data[0], _y, _width * _height);
        memcpy(piml->frame->data[1], _u, _width * _height / 4);
        memcpy(piml->frame->data[2], _v, _width * _height / 4);
        */

        return 0;
    }

    int EyerAVFrame::GetAudioData(unsigned char * data)
    {
        memcpy(data, piml->frame->data[0], 8192 / 2);
        memcpy(data + 8192 / 2, piml->frame->data[1], 8192 / 2);
        return 0;
    }

    int EyerAVFrame::GetChannels()
    {
        return piml->frame->channels;
    }

    int EyerAVFrame::GetSampleRate()
    {
        return piml->frame->sample_rate;
    }

    int EyerAVFrame::GetNBSamples()
    {

        return piml->frame->nb_samples;
    }

    int EyerAVFrame::GetPerSampleSize()
    {
        int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)piml->frame->format);
        return sizePerSample;
    }

    int EyerAVFrame::InitAACFrame(int channels)
    {
        if(channels >= AV_NUM_DATA_POINTERS){
            channels = AV_NUM_DATA_POINTERS;
        }

        piml->frame->format = AVSampleFormat::AV_SAMPLE_FMT_FLTP;
        piml->frame->channels = channels;
        piml->frame->nb_samples = 1024;

        for(int channelIndex=0; channelIndex<channels; channelIndex++){
            int len = GetPerSampleSize() * GetNBSamples();

            unsigned char * d = (unsigned char *)malloc(len);
            memset(d, 0, len);

            piml->frame->data[channelIndex] = d;
            dataManager.push_back(d);
        }
        return 0;
    }

    float EyerAVFrame::GetAudioFloatData(int channel, int index)
    {
        if(channel >= GetChannels()){
            return 0;
        }

        if(index >= GetNBSamples()){
            return 0;
        }

        float * d = (float *)piml->frame->data[channel];
        return d[index];
    }

    int EyerAVFrame::SetAudioFloatData(int channel, int index, float d)
    {
        if(channel >= GetChannels()){
            return 0;
        }

        if(index >= GetNBSamples()){
            return 0;
        }

        float * dArr = (float *)piml->frame->data[channel];
        dArr[index] = d;

        return 0;
    }

    int EyerAVFrame::SetAudioData(unsigned char * _data, int _dataLen, int nbSamples, int channel, EyerAVFormat _format)
    {
        if(_format == EyerAVFormat::EYER_AV_SAMPLE_FMT_FLTP){
            // float, planar
            unsigned char * data = (unsigned char *)malloc(_dataLen);
            dataManager.push_back(data);

            memcpy(data, _data, _dataLen);

            piml->frame->format = AV_SAMPLE_FMT_FLTP;
            piml->frame->channels = channel;
            piml->frame->nb_samples = nbSamples;
            int ret = avcodec_fill_audio_frame(piml->frame, channel, AV_SAMPLE_FMT_FLTP, (const uint8_t *) data, _dataLen, 0);
            // printf("avcodec_fill_audio_frame ret:%d\n", ret);

            /*
            printf("====================================================\n");
            printf("Linesize 0:%d\n", piml->frame->linesize[0]);
            printf("Linesize 1:%d\n", piml->frame->linesize[1]);
            printf("Channels:%d\n", piml->frame->channels);
            printf("nb_samples:%d\n", piml->frame->nb_samples);
            printf("channel_layout:%lld\n", piml->frame->channel_layout);
            printf("format:%lld\n", piml->frame->format);
            */

            return 0;
        }
        return -1;
    }
}
