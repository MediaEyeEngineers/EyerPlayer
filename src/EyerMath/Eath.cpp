#include "Eath.hpp"

#include <math.h>

namespace Eyer
{
    float Eath::DegreesToRadians(float degrees)
    {
        return degrees * float(EYER_PI/180);
    }

    float Eath::DifferenceProduct(const Eatrix2x1<float> & a,  const Eatrix2x1<float> & b, const Eatrix2x1<float> & c)
    {
        return (a.x()-c.x())*(b.y()-c.y())-(b.x()-c.x())*(a.y()-c.y());
    }

    bool Eath::IsLineCross(const Eatrix2x1<float> & a, const Eatrix2x1<float> & b, const Eatrix2x1<float> & c, const Eatrix2x1<float> & d)
    {

        if ( std::max(a.x(), b.x()) < std::min(c.x(), d.x()) )
        {
            return false;
        }
        if ( std::max(a.y(), b.y()) < std::min(c.y(), d.y()) )
        {
            return false;
        }
        if ( std::max(c.x(), d.x()) < std::min(a.x(), b.x()) )
        {
            return false;
        }
        if ( std::max(c.y(), d.y()) < std::min(a.y(), b.y()) )
        {
            return false;
        }
        if ( DifferenceProduct(c, b, a) * DifferenceProduct(b, d, a)<0 )
        {
            return false;
        }
        if ( DifferenceProduct(a, d, c) * DifferenceProduct(d, b, c)<0 )
        {
            return false;
        }
        return true;
    }
}