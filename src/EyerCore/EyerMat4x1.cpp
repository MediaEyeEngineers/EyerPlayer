#include "EyerMath.hpp"
#include <math.h>

namespace Eyer {
    EyerMat4x1::EyerMat4x1() : EyerMat(4, 1)
    {

    }

    EyerMat4x1::EyerMat4x1(float x, float y, float z, float w) : EyerMat(4, 1)
    {
        SetX(x);
        SetY(y);
        SetZ(z);
        SetW(w);
    }

    EyerMat4x1::~EyerMat4x1()
    {

    }

    float EyerMat4x1::x()
    {
        return mat[0][0];
    }

    float EyerMat4x1::y()
    {
        return mat[1][0];
    }

    float EyerMat4x1::z()
    {
        return mat[2][0];
    }

    float EyerMat4x1::w()
    {
        return mat[3][0];
    }

    int EyerMat4x1::SetX(float x)
    {
        mat[0][0] = x;
        return 0;
    }

    int EyerMat4x1::SetY(float y)
    {
        mat[1][0] = y;
        return 0;
    }

    int EyerMat4x1::SetZ(float z)
    {
        mat[2][0] = z;
        return 0;
    }

    int EyerMat4x1::SetW(float w)
    {
        mat[3][0] = w;
        return 0;
    }


    float EyerMat4x1::x1()
    {
        return x();
    }

    float EyerMat4x1::y1()
    {
        return y();
    }

    float EyerMat4x1::x2()
    {
        return z();
    }

    float EyerMat4x1::y2()
    {
        return w();
    }

    int EyerMat4x1::SetXY1(float x, float y)
    {
        SetX(x);
        SetY(y);

        return 0;
    }

    int EyerMat4x1::SetXY2(float x, float y)
    {
        SetZ(x);
        SetW(y);
        return 0;
    }

    float EyerMat4x1::Norm()
    {
        return sqrt(x() * x() + y() * y() + z() * z() + w() * w());
    }
}