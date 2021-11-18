#ifndef EYERLIB_EYERAVENCODERPARAM_HPP
#define EYERLIB_EYERAVENCODERPARAM_HPP

#include "EyerAVRational.hpp"

namespace Eyer
{
    enum CodecId
    {
        CODEC_ID_UNKNOW = 0,
        CODEC_ID_H264 = 1,
        CODEC_ID_AAC = 2,
        CODEC_ID_GIF = 3,
        CODEC_ID_MP3 = 4
    };

    class EyerAVEncoderParam {
    public:
        EyerAVEncoderParam();
        ~EyerAVEncoderParam();

        EyerAVEncoderParam(const EyerAVEncoderParam & params);
        EyerAVEncoderParam & operator = (const EyerAVEncoderParam & params);

        int InitH264(int width, int height, const EyerAVRational & _timebase);
        int InitAAC(int sample_rate);
        int InitMP3(int sample_rate);

    public:
        CodecId codecId = CodecId::CODEC_ID_UNKNOW;
        int width = 0;
        int height = 0;

        int sample_rate = 44100;

        EyerAVRational timebase;
    };
}

#endif //EYERLIB_EYERAVENCODERPARAM_HPP
