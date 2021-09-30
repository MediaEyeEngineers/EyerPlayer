#ifndef EYERLIB_EYERAVPIXELFORMAT_HPP
#define EYERLIB_EYERAVPIXELFORMAT_HPP

namespace Eyer
{
    class EyerAVPixelFormat
    {
    public:
        static EyerAVPixelFormat YUV420P;
        static EyerAVPixelFormat YUYV422;
        static EyerAVPixelFormat RGB24;
        static EyerAVPixelFormat RGBA;

        EyerAVPixelFormat();
        EyerAVPixelFormat(int id, int ffmpegId);

        bool operator == (const EyerAVPixelFormat & format);

        int id = 0;
        int ffmpegId = 0;
    };
}

#endif //EYERLIB_EYERAVPIXELFORMAT_HPP