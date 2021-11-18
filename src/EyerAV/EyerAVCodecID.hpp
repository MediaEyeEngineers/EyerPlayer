#ifndef EYERLIB_EYERAVCODECID_HPP
#define EYERLIB_EYERAVCODECID_HPP

namespace Eyer
{
    class EyerAVCodecID
    {
    public:
        static EyerAVCodecID CODEC_ID_H264;
        static EyerAVCodecID CODEC_ID_H265;
        static EyerAVCodecID CODEC_ID_MP3;
        static EyerAVCodecID CODEC_ID_AAC;

        EyerAVCodecID();
        EyerAVCodecID(int id, int ffmpegId);

        bool operator == (const EyerAVCodecID & format);

        int id = 0;
        int ffmpegId = 0;
    };
}

#endif //EYERLIB_EYERAVCODECID_HPP
