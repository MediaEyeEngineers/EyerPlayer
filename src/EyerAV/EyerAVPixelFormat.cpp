#include "EyerAVPixelFormat.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVPixelFormat EyerAVPixelFormat::UNKNOW     (-1, -1);
    EyerAVPixelFormat EyerAVPixelFormat::YUV420P    (1, AV_PIX_FMT_YUV420P);
    EyerAVPixelFormat EyerAVPixelFormat::YUVJ420P   (2, AV_PIX_FMT_YUVJ420P);
    EyerAVPixelFormat EyerAVPixelFormat::NV12       (3, AV_PIX_FMT_NV12);
    EyerAVPixelFormat EyerAVPixelFormat::NV21       (4, AV_PIX_FMT_NV21);
    EyerAVPixelFormat EyerAVPixelFormat::YUYV422    (5, AV_PIX_FMT_YUYV422);
    EyerAVPixelFormat EyerAVPixelFormat::RGB24      (6, AV_PIX_FMT_RGB24);
    EyerAVPixelFormat EyerAVPixelFormat::RGBA       (7, AV_PIX_FMT_RGBA);

    EyerAVPixelFormat::EyerAVPixelFormat()
        : EyerAVPixelFormat(3, AV_PIX_FMT_RGB24)
    {

    }

    EyerAVPixelFormat::EyerAVPixelFormat(int _id, int _ffmpegId)
    {
        id = _id;
        ffmpegId = _ffmpegId;
    }

    bool EyerAVPixelFormat::operator == (const EyerAVPixelFormat & format)
    {
        return id == format.id;
    }

    EyerAVPixelFormat::EyerAVPixelFormat(const EyerAVPixelFormat & pixelFormat)
    {
        *this = pixelFormat;
    }

    EyerAVPixelFormat & EyerAVPixelFormat::operator = (const EyerAVPixelFormat & pixelFormat)
    {
        id = pixelFormat.id;
        ffmpegId = pixelFormat.ffmpegId;
        return *this;
    }

    EyerAVPixelFormat EyerAVPixelFormat::GetByFFmpegId(int ffmpegId)
    {
        if(ffmpegId == AV_PIX_FMT_YUV420P){
            return YUV420P;
        }
        if(ffmpegId == AV_PIX_FMT_YUYV422){
            return YUYV422;
        }
        if(ffmpegId == AV_PIX_FMT_RGB24){
            return RGB24;
        }
        if(ffmpegId == AV_PIX_FMT_RGBA){
            return RGBA;
        }
        if(ffmpegId == AV_PIX_FMT_YUVJ420P){
            return YUVJ420P;
        }
        if(ffmpegId == AV_PIX_FMT_NV12){
            return NV12;
        }
        if(ffmpegId == AV_PIX_FMT_NV21){
            return NV21;
        }
        return UNKNOW;
    }
}