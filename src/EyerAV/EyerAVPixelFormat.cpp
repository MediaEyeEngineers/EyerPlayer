#include "EyerAVPixelFormat.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVPixelFormat EyerAVPixelFormat::YUV420P    (1, AV_PIX_FMT_YUV420P);
    EyerAVPixelFormat EyerAVPixelFormat::YUYV422    (2, AV_PIX_FMT_YUYV422);
    EyerAVPixelFormat EyerAVPixelFormat::RGB24      (3, AV_PIX_FMT_RGB24);
    EyerAVPixelFormat EyerAVPixelFormat::RGBA       (4, AV_PIX_FMT_RGBA);

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
}