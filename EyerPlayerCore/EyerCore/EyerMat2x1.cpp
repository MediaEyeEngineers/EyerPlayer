#include "EyerMath.hpp"
#include <math.h>

namespace Eyer {
    EyerMat2x1::EyerMat2x1() : EyerMat(2, 1)
    {

    }

    EyerMat2x1::EyerMat2x1(const EyerMat & m) : EyerMat(2, 1)
    {
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = 0.0f;
            }
        }
        
        if(this->row != m.row){
            return;
        }
        if(this->col != m.col){
            return;
        }

        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = m.mat[i][j];
            }
        }
    }

    EyerMat2x1::EyerMat2x1(float x, float y) : EyerMat(2, 1)
    {
        SetX(x);
        SetY(y);
    }

    EyerMat2x1::~EyerMat2x1()
    {

    }

    float EyerMat2x1::x()
    {
        return mat[0][0];
    }

    float EyerMat2x1::y()
    {
        return mat[1][0];
    }

    int EyerMat2x1::SetX(float x)
    {
        mat[0][0] = x;
        return 0;
    }

    int EyerMat2x1::SetY(float y)
    {
        mat[1][0] = y;
        return 0;
    }

    float EyerMat2x1::Norm()
    {
        return sqrt(x() * x() + y() * y());
    }
}