#include "EyerAVEncoderParam.hpp"

namespace Eyer
{
    EyerAVEncoderParam::EyerAVEncoderParam()
    {

    }

    EyerAVEncoderParam::~EyerAVEncoderParam()
    {

    }

    EyerAVEncoderParam::EyerAVEncoderParam(const EyerAVEncoderParam & params)
    {
        *this = params;
    }

    EyerAVEncoderParam & EyerAVEncoderParam::operator = (const EyerAVEncoderParam & params)
    {
        codecId     = params.codecId;
        width       = params.width;
        height      = params.height;
        sample_rate = params.sample_rate;
        timebase    = params.timebase;
        return *this;
    }

    int EyerAVEncoderParam::InitH264(int _width, int _height, const EyerAVRational & _timebas)
    {
        codecId         = CodecId::CODEC_ID_H264;
        width           = _width;
        height          = _height;
        timebase        = _timebas;

        return 0;
    }

    int EyerAVEncoderParam::InitAAC(int _sample_rate)
    {
        codecId         = CodecId::CODEC_ID_AAC;
        sample_rate     = _sample_rate;
        return 0;
    }

    int EyerAVEncoderParam::InitMP3(int _sample_rate)
    {
        codecId         = CodecId::CODEC_ID_MP3;
        sample_rate     = _sample_rate;
        return 0;
    }
}