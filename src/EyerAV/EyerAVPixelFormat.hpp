#ifndef EYERLIB_EYERAVPIXELFORMAT_HPP
#define EYERLIB_EYERAVPIXELFORMAT_HPP

namespace Eyer
{
    class EyerAVPixelFormat
    {
    public:
        static EyerAVPixelFormat YUV420P;
        static EyerAVPixelFormat YUVJ420P;
        static EyerAVPixelFormat YUYV422;
        static EyerAVPixelFormat NV12;
        static EyerAVPixelFormat NV21;

        static EyerAVPixelFormat RGB24;
        static EyerAVPixelFormat RGBA;
        static EyerAVPixelFormat UNKNOW;

        EyerAVPixelFormat();
        EyerAVPixelFormat(const EyerAVPixelFormat & pixelFormat);
        EyerAVPixelFormat(int id, int ffmpegId);

        EyerAVPixelFormat & operator = (const EyerAVPixelFormat & pixelFormat);

        bool operator == (const EyerAVPixelFormat & format);
        bool operator != (const EyerAVPixelFormat & format);

        static EyerAVPixelFormat GetByFFmpegId(int ffmpegId);

        int id = 0;
        int ffmpegId = 0;
    };
}

#endif //EYERLIB_EYERAVPIXELFORMAT_HPP