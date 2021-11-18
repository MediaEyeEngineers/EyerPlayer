#ifndef EYERLIB_EYERAVCODECTYPE_HPP
#define EYERLIB_EYERAVCODECTYPE_HPP

namespace Eyer
{
    class EyerAVCodecType
    {
    public:
        static EyerAVCodecType MEDIA_TYPE_VIDEO;
        static EyerAVCodecType MEDIA_TYPE_AUDIO;

        EyerAVCodecType();
        EyerAVCodecType(int id, int ffmpegId);

        bool operator == (const EyerAVCodecType & format);

        int id = 0;
        int ffmpegId = 0;
    };
}

#endif //EYERLIB_EYERAVCODECTYPE_HPP
