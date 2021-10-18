#include "EyerAVStream.hpp"

#include "EyerAVStreamPrivate.hpp"

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
        stream.piml->codecpar = nullptr;
    }

    EyerAVStream & EyerAVStream::operator = (const EyerAVStream & stream)
    {
        avcodec_parameters_copy(piml->codecpar, stream.piml->codecpar);
        piml->timebase = stream.piml->timebase;
        piml->stream_id = stream.piml->stream_id;
        return *this;
    }

    int EyerAVStream::GetStreamId()
    {
        return piml->stream_id;
    }
}