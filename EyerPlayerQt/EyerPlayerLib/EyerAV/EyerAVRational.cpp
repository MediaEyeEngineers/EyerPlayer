#include "EyerAV.hpp"

namespace Eyer
{
    EyerAVRational::EyerAVRational()
    {
        num = 0;
        den = 0;
    }

    EyerAVRational::EyerAVRational(const EyerAVRational & avRational)
    {
        *this = avRational;
    }

    EyerAVRational::~EyerAVRational()
    {

    }

    EyerAVRational & EyerAVRational::operator = (const EyerAVRational & avRational)
    {
        num = avRational.num;
        den = avRational.den;

        return *this;
    }
}