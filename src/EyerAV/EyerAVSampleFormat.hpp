#ifndef EYERLIB_EYERAVSAMPLEFORMAT_HPP
#define EYERLIB_EYERAVSAMPLEFORMAT_HPP

namespace Eyer
{
    class EyerAVSampleFormat
    {
    public:
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

        EyerAVSampleFormat(int id);

        bool operator == (const EyerAVSampleFormat & format);

        int id = 0;
    };
}

#endif //EYERLIB_EYERAVSAMPLEFORMAT_HPP
