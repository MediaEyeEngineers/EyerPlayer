#include "EyerAVEncoderParam.hpp"

#include "EyerAVStream.hpp"
#include "EyerAVStreamPrivate.hpp"
#include "EyerCore/EyerCore.hpp"

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

    int EyerAVEncoderParam::InitH264(int width, int height, int fps)
    {
        Eyer::EyerAVRational videoTimebase;
        videoTimebase.num = 1;
        videoTimebase.den = fps;

        return InitH264(width, height, videoTimebase);
    }

    int EyerAVEncoderParam::InitH264(int _width, int _height, const EyerAVRational & _timebase)
    {
        codecId         = CodecId::CODEC_ID_H264;
        width           = _width;
        height          = _height;
        timebase        = _timebase;

        return 0;
    }

    int EyerAVEncoderParam::InitH265(int width, int height, int fps)
    {
        Eyer::EyerAVRational videoTimebase;
        videoTimebase.num = 1;
        videoTimebase.den = fps;

        return InitH265(width, height, videoTimebase);
    }

    int EyerAVEncoderParam::InitH265(int _width, int _height, const EyerAVRational & _timebase)
    {
        codecId         = CodecId::CODEC_ID_H265;
        width           = _width;
        height          = _height;
        timebase        = _timebase;

        return 0;
    }

    int EyerAVEncoderParam::InitAAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = CodecId::CODEC_ID_AAC;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitFDKAAC(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = CodecId::CODEC_ID_FDK_AAC;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitMP3(EyerAVChannelLayout _channelLayout, EyerAVSampleFormat _sampleFormat, int _sample_rate)
    {
        codecId         = CodecId::CODEC_ID_MP3;
        channelLayout   = _channelLayout;
        sample_rate     = _sample_rate;
        sampleFormat    = _sampleFormat;
        return 0;
    }

    int EyerAVEncoderParam::InitJPEG(int _width, int _height)
    {
        codecId         = CodecId::CODEC_ID_JPEG;
        width           = _width;
        height          = _height;
        EyerAVRational _timebase;
        _timebase.den = 25;
        _timebase.num = 1;
        timebase        = _timebase;

        return 0;
    }

    int EyerAVEncoderParam::InitPNG(int _width, int _height)
    {
        codecId         = CodecId::CODEC_ID_PNG;
        width           = _width;
        height          = _height;
        EyerAVRational _timebase;
        _timebase.den = 25;
        _timebase.num = 1;
        timebase        = _timebase;

        return 0;
    }

    int EyerAVEncoderParam::InitFromStream(const EyerAVStream & _straem)
    {
        // 264 和 264 都变成 264
        if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_H264){
            codecId = CodecId::CODEC_ID_H264;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_H265){
            codecId = CodecId::CODEC_ID_H264;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_MJPEG){
            codecId = CodecId::CODEC_ID_JPEG;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_PNG){
            codecId = CodecId::CODEC_ID_PNG;
            pixel_fmt = _straem.piml->codecpar->format;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_MP3){
            codecId = CodecId::CODEC_ID_MP3;
        }
        else if(_straem.piml->codecpar->codec_id == AV_CODEC_ID_AAC){
            codecId = CodecId::CODEC_ID_MP3;
        }
        else {
            EyerLog("Codec ID: %d\n", _straem.piml->codecpar->codec_id);
            if(_straem.piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO){
                codecId = CodecId::CODEC_ID_H264;
            }
            if(_straem.piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
                codecId = CodecId::CODEC_ID_MP3;
            }
        }
        return 0;
    }

    int EyerAVEncoderParam::SetTimebase(const EyerAVRational & _timebase)
    {
        timebase = _timebase;
        return 0;
    }

    int EyerAVEncoderParam::SetWH(int _width, int _height)
    {
        width = _width;
        height = _height;
        return 0;
    }
}