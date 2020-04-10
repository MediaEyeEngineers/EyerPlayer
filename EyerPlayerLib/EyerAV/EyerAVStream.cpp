#include "EyerAV.hpp"

#include "EyerAVStreamPrivate.hpp"

namespace Eyer
{
    EyerAVStream::EyerAVStream()
    {
        piml = new EyerAVStreamPrivate();
        piml->codecContext = avcodec_alloc_context3(nullptr);
    }
    
    EyerAVStream::~EyerAVStream()
    {
        if(piml->codecContext != nullptr){
            avcodec_free_context(&piml->codecContext);
            piml->codecContext = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    EyerAVStreamType EyerAVStream::GetStreamType()
    {
        if(piml->codecContext->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO){
            return EyerAVStreamType::STREAM_TYPE_VIDEO;
        }
        if(piml->codecContext->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
            return EyerAVStreamType::STREAM_TYPE_AUDIO;
        }

        return EyerAVStreamType::STREAM_TYPE_AUDIO;
    }

    int EyerAVStream::SetDuration(double _duration)
    {
        duration = _duration;
        return 0;
    }

    double EyerAVStream::GetDuration()
    {
        return duration;
    }

    int EyerAVStream::GetWidth()
    {
        return piml->codecContext->width;
    }

    int EyerAVStream::GetHeight()
    {
        return piml->codecContext->height;
    }
}
