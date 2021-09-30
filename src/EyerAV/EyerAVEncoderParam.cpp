#include "EyerAVEncoderParam.hpp"

namespace Eyer
{
    EyerAVEncoderParam::EyerAVEncoderParam()
    {

    }

    EyerAVEncoderParam::~EyerAVEncoderParam()
    {

    }

    int EyerAVEncoderParam::InitH264(int _width, int _height, const EyerAVRational & _timebas)
    {
        codecId         = CodecId::CODEC_ID_H264;
        width           = _width;
        height          = _height;
        timebase        = _timebas;

        return 0;
    }

    int EyerAVEncoderParam::InitAAC()
    {
        codecId         = CodecId::CODEC_ID_AAC;
        return 0;
    }
}