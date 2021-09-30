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
}