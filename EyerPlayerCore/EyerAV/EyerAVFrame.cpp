#include "EyerAVAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/imgutils.h>
#include <libavcodec/avcodec.h>
#include <libavutil/pixdesc.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

#include "EyerAVEncoderPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

namespace Eyer {
    EyerAVFrame::EyerAVFrame()
    {
        piml = new EyerAVFramePrivate();
        piml->frame = av_frame_alloc();
    }

    EyerAVFrame::~EyerAVFrame()
    {
        av_frame_unref(piml->frame);
        av_frame_free(&piml->frame);
        if (piml != nullptr) {
            delete piml;
            piml = nullptr;
        }
    }

    EyerAVFrame::EyerAVFrame(const EyerAVFrame & frame) : EyerAVFrame()
    {
        *this = frame;
    }

    EyerAVFrame & EyerAVFrame::operator = (const EyerAVFrame & frame)
    {
        av_frame_copy(piml->frame, frame.piml->frame);
        av_frame_ref(piml->frame, frame.piml->frame);
        return *this;
    }

    int EyerAVFrame::GetWidth() const
    {
        return piml->frame->width;
    }

    int EyerAVFrame::GetHeight() const
    {
        return piml->frame->height;
    }

    int EyerAVFrame::GetYData(unsigned char * yData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int w = width;
        int h = height;
        
        EyerYUVLen yuvLen;
        EyerAVTool::GetYUVLen(w, h, yuvLen, GetPixFormat());

        w = yuvLen.yWidth;
        h = yuvLen.yHeight;

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

        int w = width;
        int h = height;
        
        EyerYUVLen yuvLen;
        EyerAVTool::GetYUVLen(w, h, yuvLen, GetPixFormat());

        w = yuvLen.uWidth;
        h = yuvLen.uHeight;

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

        int w = width;
        int h = height;
        
        EyerYUVLen yuvLen;
        EyerAVTool::GetYUVLen(w, h, yuvLen, GetPixFormat());

        w = yuvLen.vWidth;
        h = yuvLen.vHeight;

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(vData + offset, piml->frame->data[2] + i * piml->frame->linesize[2], w);
            offset += w;
        }
        return 0;
    }

    int EyerAVFrame::GetUVData(unsigned char * uvData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int w = width;
        int h = height;
        
        EyerYUVLen yuvLen;
        EyerAVTool::GetYUVLen(w, h, yuvLen, GetPixFormat());

        w = yuvLen.yWidth;
        h = yuvLen.yHeight;

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(uvData + offset, piml->frame->data[1] + i * piml->frame->linesize[1], w);
            offset += w;
        }

        return 0;
    }

    int EyerAVFrame::GetRGBAData(unsigned char * rgbaData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int w = width * 4;
        int h = height;

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(rgbaData + offset, piml->frame->data[0] + i * piml->frame->linesize[0], w);
            offset += w;
        }

        return 0;
    }

    int EyerAVFrame::SetPTS(int64_t pts)
    {
        piml->frame->pts = pts;
        return 0;
    }

    int64_t EyerAVFrame::GetPTS()
    {
        return piml->frame->pts;
    }

    double EyerAVFrame::GetSecPTS()
    {
        return 0.0;
    }

    int EyerAVFrame::SetNULLData(int w, int h, EyerAVPixelFormat format)
    {
        av_frame_unref(piml->frame);

        AVPixelFormat ffFormat = (AVPixelFormat)ToFFmpegPixelFormat(format);

        piml->frame->format = ffFormat;
        piml->frame->width = w;
        piml->frame->height = h;
        piml->frame->extended_data = piml->frame->data;

        av_frame_get_buffer(piml->frame, 16);

        return 0;
    }

    int EyerAVFrame::Scale(EyerAVFrame & dstFrame, const int dstW, const int dstH, const EyerAVPixelFormat format)
    {
        dstFrame.SetNULLData(dstW, dstH, format);
        AVPixelFormat ffFormat = (AVPixelFormat)ToFFmpegPixelFormat(format);

        int srcW = GetWidth();
        int srcH = GetHeight();

        AVPixelFormat srcFormat = (AVPixelFormat)(piml->frame->format);
        SwsContext * swsContext = sws_getContext(srcW, srcH, srcFormat, dstW, dstH, ffFormat, SWS_FAST_BILINEAR, NULL, NULL, NULL);
        
        if(swsContext == nullptr){
            return -1;
        }
        
        sws_scale(
            swsContext,
            (const uint8_t **)piml->frame->data,
            piml->frame->linesize,
            0,
            srcH,
            
            dstFrame.piml->frame->data,
            dstFrame.piml->frame->linesize
            );

        sws_freeContext(swsContext);
        
        return 0;
    }

    EyerAVPixelFormat EyerAVFrame::GetPixFormat() const
    {
        return ToEyerPixelFormat(piml->frame->format);;
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

        av_frame_get_buffer(piml->frame, 16);

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



    int EyerAVFrame::GetInfo()
    {
        return 0;
    }

    int EyerAVFrame::SetLast()
    {
        piml->isLastPacket = 1;
        return 0;
    }

    int EyerAVFrame::IsLast()
    {
        return piml->isLastPacket;
    }
}