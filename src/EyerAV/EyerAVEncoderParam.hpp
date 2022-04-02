#ifndef EYERLIB_EYERAVENCODERPARAM_HPP
#define EYERLIB_EYERAVENCODERPARAM_HPP

#include "EyerAVRational.hpp"
#include "EyerAVStream.hpp"
#include "EyerAVChannelLayout.hpp"
#include "EyerAVSampleFormat.hpp"

namespace Eyer
{
    enum CodecId
    {
        CODEC_ID_UNKNOW = 0,
        CODEC_ID_H264 = 1,

        CODEC_ID_AAC = 2,
        CODEC_ID_GIF = 3,
        CODEC_ID_MP3 = 4,
        CODEC_ID_JPEG = 5,
        CODEC_ID_PNG = 6,

        CODEC_ID_FDK_AAC = 7,
        CODEC_ID_H265 = 8,
    };

    class EyerAVEncoderParam {
    public:
        EyerAVEncoderParam();
        ~EyerAVEncoderParam();

        EyerAVEncoderParam(const EyerAVEncoderParam & params);
        EyerAVEncoderParam & operator = (const EyerAVEncoderParam & params);

        int InitH264(int width, int height, int fps);
        int InitH264(int width, int height, const EyerAVRational & _timebase);

        int InitH265(int width, int height, int fps);
        int InitH265(int width, int height, const EyerAVRational & _timebase);

        int InitAAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitFDKAAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitMP3(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate);
        int InitJPEG(int width, int height);
        int InitPNG(int width, int height);

        int InitFromStream(const EyerAVStream & straem);
        int SetTimebase(const EyerAVRational & timebase);
        int SetWH(int width, int height);

    public:
        CodecId codecId = CodecId::CODEC_ID_UNKNOW;
        int width = 0;
        int height = 0;

        int sample_rate = 44100;
        EyerAVChannelLayout channelLayout;
        EyerAVSampleFormat sampleFormat;

        int pixel_fmt = 0;

        EyerAVRational timebase;
    };
}

#endif //EYERLIB_EYERAVENCODERPARAM_HPP
