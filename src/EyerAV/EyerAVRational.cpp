#include "EyerAVRational.hpp"

namespace Eyer
{
    EyerAVRational::EyerAVRational()
    {

    }

    EyerAVRational::EyerAVRational(int _num, int _den)
    {
        num = _num;
        den = _den;
    }

    EyerAVRational::~EyerAVRational()
    {

    }

    EyerAVRational::EyerAVRational(const EyerAVRational & rational)
    {
        *this = rational;
    }

    EyerAVRational & EyerAVRational::operator = (const EyerAVRational & rational)
    {
        num = rational.num;
        den = rational.den;
        return *this;
    }
}