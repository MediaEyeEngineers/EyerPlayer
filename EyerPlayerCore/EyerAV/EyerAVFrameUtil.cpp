#include "EyerAVAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/imgutils.h>
}

#include "EyerAVEncoderPrivate.hpp"
#include "EyerAVFramePrivate.hpp"

namespace Eyer {
    int EyerAVFrame::ToFFmpegPixelFormat(const EyerAVPixelFormat format)
    {
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_UNKNOW){
            return AVPixelFormat::AV_PIX_FMT_NONE;
        }
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P){
            return AVPixelFormat::AV_PIX_FMT_YUV420P;
        }
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
            return AVPixelFormat::AV_PIX_FMT_YUVJ420P;
        }
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVNV12){
            return AVPixelFormat::AV_PIX_FMT_NV12;
        }
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVNV21){
            return AVPixelFormat::AV_PIX_FMT_NV21;
        }
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV422P){
            return AVPixelFormat::AV_PIX_FMT_YUV422P;
        }
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUYV422){
            return AVPixelFormat::AV_PIX_FMT_YUYV422;
        }
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P){
            return AVPixelFormat::AV_PIX_FMT_YUV444P;
        }
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_RGBA){
            return AVPixelFormat::AV_PIX_FMT_RGBA;
        }

        return AVPixelFormat::AV_PIX_FMT_NONE;
    }

    EyerAVPixelFormat EyerAVFrame::ToEyerPixelFormat(const int format)
    {
        if(format == AVPixelFormat::AV_PIX_FMT_YUV420P){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P;
        }
        if(format == AVPixelFormat::AV_PIX_FMT_YUVJ420P){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P;
        }
        if(format == AVPixelFormat::AV_PIX_FMT_NV12){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVNV12;
        }
        if(format == AVPixelFormat::AV_PIX_FMT_NV21){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVNV21;
        }
        if(format == AVPixelFormat::AV_PIX_FMT_YUV422P || format == AVPixelFormat::AV_PIX_FMT_YUVJ422P){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV422P;
        }
        if(format == AVPixelFormat::AV_PIX_FMT_YUV444P || format == AVPixelFormat::AV_PIX_FMT_YUVJ444P){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P;
        }
        if(format == AVPixelFormat::AV_PIX_FMT_YUYV422){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUYV422;
        }
        if(format == AVPixelFormat::AV_PIX_FMT_RGBA){
            return EyerAVPixelFormat::Eyer_AV_PIX_FMT_RGBA;
        }

        return EyerAVPixelFormat::Eyer_AV_PIX_FMT_UNKNOW;
    }
}