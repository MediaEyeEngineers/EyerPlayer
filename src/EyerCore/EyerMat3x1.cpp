#include "EyerMath.hpp"
#include <math.h>

namespace Eyer {
    EyerMat3x1::EyerMat3x1() : EyerMat(3, 1)
    {

    }

    EyerMat3x1::~EyerMat3x1()
    {

    }

    float EyerMat3x1::x()
    {
        return mat[0][0];
    }

    float EyerMat3x1::y()
    {
        return mat[1][0];
    }

    float EyerMat3x1::z()
    {
        return mat[2][0];
    }

    int EyerMat3x1::SetX(float x)
    {
        mat[0][0] = x;
        return 0;
    }

    int EyerMat3x1::SetY(float y)
    {
        mat[1][0] = y;
        return 0;
    }

    int EyerMat3x1::SetZ(float z)
    {
        mat[2][0] = z;
        return 0;
    }

    float EyerMat3x1::Norm()
    {
        return sqrt(x() * x() + y() * y() + z() * z());
    }
}