#include "EyerAVStream.hpp"

#include "EyerAVStreamPrivate.hpp"
#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVStream::EyerAVStream()
    {
        piml = new EyerAVStreamPrivate();
        piml->codecpar = avcodec_parameters_alloc();
    }

    EyerAVStream::~EyerAVStream()
    {
        if(piml->codecpar != nullptr){
            avcodec_parameters_free(&piml->codecpar);
            piml->codecpar = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    EyerAVStream::EyerAVStream(const EyerAVStream & stream)
        : EyerAVStream()
    {
        *this = stream;
    }

    EyerAVStream::EyerAVStream(EyerAVStream && stream)
    {
        piml = new EyerAVStreamPrivate();
        piml->codecpar = stream.piml->codecpar;
        piml->stream_id = stream.piml->stream_id;
        piml->duration = stream.piml->duration;
        stream.piml->codecpar = nullptr;
    }

    EyerAVStream & EyerAVStream::operator = (const EyerAVStream & stream)
    {
        avcodec_parameters_copy(piml->codecpar, stream.piml->codecpar);
        piml->timebase      = stream.piml->timebase;
        piml->stream_id     = stream.piml->stream_id;
        piml->duration      = stream.piml->duration;
        return *this;
    }

    int EyerAVStream::GetStreamId()
    {
        return piml->stream_id;
    }

    double EyerAVStream::GetDuration() const
    {
        return piml->duration;
    }

    EyerAVCodecType EyerAVStream::GetType()
    {
        if(piml->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            return EyerAVCodecType::MEDIA_TYPE_VIDEO;
        }
        else if(piml->codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
            return EyerAVCodecType::MEDIA_TYPE_AUDIO;
        }

        return EyerAVCodecType::MEDIA_TYPE_VIDEO;
    }

    int EyerAVStream::GetWidth()
    {
        return piml->codecpar->width;
    }

    int EyerAVStream::GetHeight()
    {
        return piml->codecpar->height;
    }

    EyerAVCodecID EyerAVStream::GetCodecID()
    {
        if(piml->codecpar->codec_id == AV_CODEC_ID_H264){
            return EyerAVCodecID::CODEC_ID_H264;
        }
        else if(piml->codecpar->codec_id == AV_CODEC_ID_MP3){
            return EyerAVCodecID::CODEC_ID_MP3;
        }
        else if(piml->codecpar->codec_id == AV_CODEC_ID_AAC){
            return EyerAVCodecID::CODEC_ID_AAC;
        }
        else if(piml->codecpar->codec_id == AV_CODEC_ID_H265){
            return EyerAVCodecID::CODEC_ID_H265;
        }
        return EyerAVCodecID::CODEC_ID_MP3;
    }
}