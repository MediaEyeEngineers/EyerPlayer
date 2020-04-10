//
// Created by redknot on 2020/3/22.
//

#include "EyerAV.hpp"

namespace Eyer
{
    EyerAVFrameWeight::EyerAVFrameWeight()
    {

    }

    EyerAVFrameWeight::EyerAVFrameWeight(EyerAVFrame & f, float w)
    {
        if(frame != nullptr){
            delete frame;
            frame = nullptr;
        }

        frame = new EyerAVFrame(f);
        weight = w;
    }

    EyerAVFrameWeight::EyerAVFrameWeight(EyerAVFrameWeight & frameWeight)
    {
        *this = frameWeight;
    }

    EyerAVFrameWeight::~EyerAVFrameWeight()
    {
        if(frame != nullptr){
            delete frame;
            frame = nullptr;
        }
    }

    EyerAVFrameWeight & EyerAVFrameWeight::operator = (EyerAVFrameWeight & frameWeight)
    {
        if(frame != nullptr){
            delete frame;
            frame = nullptr;
        }

        frame = new EyerAVFrame(*frameWeight.frame);
        weight = frameWeight.weight;

        return *this;
    }
}