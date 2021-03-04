#include "EyerAVAV.hpp"

#include "EyerAVStreamPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"

namespace Eyer
{
    EyerAVStream::EyerAVStream()
    {
        piml = new EyerAVStreamPrivate();
        piml->codecpar = avcodec_parameters_alloc();
        piml->codec = avcodec_alloc_context3(nullptr);
    }
    
    EyerAVStream::~EyerAVStream()
    {
        if(piml->codecpar != nullptr){
            avcodec_parameters_free(&piml->codecpar);
            piml->codecpar = nullptr;
        }
        if(piml->codec != nullptr){
            avcodec_free_context(&piml->codec);
            piml->codec = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    EyerAVStream::EyerAVStream(const EyerAVStream & stream) : EyerAVStream()
    {
        *this = stream;
    }

    const EyerAVStream & EyerAVStream::operator = (const EyerAVStream & stream)
    {
        avcodec_parameters_copy(piml->codecpar, stream.piml->codecpar);
        avcodec_copy_context(piml->codec, stream.piml->codec);

        piml->type = stream.piml->type;
        streamIndex = stream.streamIndex;
        duration = stream.duration;
        timebase = stream.timebase;

        return *this;
    }

    EyerAVStreamType EyerAVStream::GetStreamType()
    {
        if(piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO){
            return EyerAVStreamType::STREAM_TYPE_VIDEO;
        }
        if(piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
            return EyerAVStreamType::STREAM_TYPE_AUDIO;
        }

        return EyerAVStreamType::STREAM_TYPE_AUDIO;
    }

    int EyerAVStream::ScalerPacketPTS(EyerAVPacket & pkt)
    {
        uint64_t pts = pkt.GetPTS();
        double ptsSec = pts * 1.0 * timebase.num / timebase.den;
        pkt.piml->ptsSec = ptsSec;
        return 0;
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
        return piml->codecpar->width;
    }

    int EyerAVStream::GetHeight()
    {
        return piml->codecpar->height;
    }

    int EyerAVStream::GetAudioChannels(){
        if(piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO){
            return -1;
        }
        if(piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
            return piml->codec->channels;
        }
        return -2;
    }

    int EyerAVStream::GetAudioSampleRate(){
        if(piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO){
            return -1;
        }
        if(piml->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
            return piml->codec->sample_rate;
        }
        return -2;
    }

    std::string EyerAVStream::GetCodecName(){
        return avcodec_get_name(piml->codec->codec_id);
    }

}
