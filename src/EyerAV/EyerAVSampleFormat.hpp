#ifndef EYERLIB_EYERAVSAMPLEFORMAT_HPP
#define EYERLIB_EYERAVSAMPLEFORMAT_HPP

namespace Eyer
{
    class EyerAVSampleFormat
    {
    public:
        static EyerAVSampleFormat UNKNOW;
        static EyerAVSampleFormat SAMPLE_FMT_U8;
        static EyerAVSampleFormat SAMPLE_FMT_S16;
        static EyerAVSampleFormat SAMPLE_FMT_S32;
        static EyerAVSampleFormat SAMPLE_FMT_FLT;
        static EyerAVSampleFormat SAMPLE_FMT_DBL;

        static EyerAVSampleFormat SAMPLE_FMT_U8P;
        static EyerAVSampleFormat SAMPLE_FMT_S16P;
        static EyerAVSampleFormat SAMPLE_FMT_S32P;
        static EyerAVSampleFormat SAMPLE_FMT_FLTP;
        static EyerAVSampleFormat SAMPLE_FMT_DBLP;

        EyerAVSampleFormat();
        EyerAVSampleFormat(int id, int ffmpegId);

        EyerAVSampleFormat(const EyerAVSampleFormat & sampleFormat);
        EyerAVSampleFormat & operator = (const EyerAVSampleFormat & sampleFormat);

        bool operator == (const EyerAVSampleFormat & format);

        static EyerAVSampleFormat GetByFFmpegId(int ffmpegId);

        int id = 0;
        int ffmpegId = 0;
    };
}

#endif //EYERLIB_EYERAVSAMPLEFORMAT_HPP
