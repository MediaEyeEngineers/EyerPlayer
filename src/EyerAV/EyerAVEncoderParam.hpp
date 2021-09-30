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
    };

    class EyerAVEncoderParam {
    public:
        EyerAVEncoderParam();
        ~EyerAVEncoderParam();

        int InitH264(int width, int height, const EyerAVRational & _timebase);
        int InitAAC();

    public:
        CodecId codecId = CodecId::CODEC_ID_UNKNOW;
        int width = 0;
        int height = 0;

        EyerAVRational timebase;
    };
}

#endif //EYERLIB_EYERAVENCODERPARAM_HPP
