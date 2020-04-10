#include "EyerMath.hpp"

#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Eyer {
    EyerMat4x4::EyerMat4x4() : EyerMat(4, 4)
    {

    }

    EyerMat4x4::EyerMat4x4(const EyerMat & _mat) : EyerMat(4, 4)
    {
        *this = _mat;
    }

    EyerMat4x4 & EyerMat4x4::operator = (const EyerMat &_mat)
    {
        if(row != _mat.row){
            return *this;
        }
        if(col != _mat.col){
            return *this;
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                mat[i][j] = _mat.mat[i][j];
            }
        }
        return *this;
    }

    EyerMat4x4::~EyerMat4x4()
    {
    }

    int EyerMat4x4::SetScale(float x, float y, float z)
    {
        mat[0][0] = x;
        mat[1][1] = y;
        mat[2][2] = z;
        mat[3][3] = 1.0f;
        return 0;
    }

    int EyerMat4x4::SetTrans(float x, float y, float z)
    {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // mat[i][j] = 0.0f;
            }
        }
        mat[0][3] = x;
        mat[1][3] = y;
        mat[2][3] = z;
        
        return 0;
    }

    int EyerMat4x4::SetRotate(float x, float y, float z, float a)
    {
        mat[0][0] = cos(a) + x * x * (1 - cos(a));      mat[0][1] = x * y * (1 - cos(a)) - z * sin(a); mat[0][2] = x * z * (1 - cos(a)) + y * sin(a);  mat[0][3] = 0.0; 
        mat[1][0] = y * x * (1 - cos(a)) + z * sin(a);  mat[1][1] = cos(a) + y * y * (1 - cos(a));     mat[1][2] = y * z * (1 - cos(a)) - x * sin(a);  mat[1][3] = 0.0;
        mat[2][0] = z * x * (1 - cos(a)) - y * sin(a);  mat[2][1] = z * y * (1 - cos(a)) + x * sin(a); mat[2][2] = cos(a) + z * z * (a - cos(a));      mat[2][3] = 0.0;
        mat[3][0] = 0.0;                                mat[3][1] = 0.0;                               mat[3][2] = 0.0;                                mat[3][3] = 1.0;
        return 0;
    }

    int EyerMat4x4::SetOrtho(float l, float r, float t, float b, float near, float far)
    {
        mat[0][0] = 2.0 / (r - l);                              mat[0][1] = 0.0f;                               mat[0][2] = 0.0f;                               mat[0][3] = - (r + l) / (r - l);
        mat[1][0] = 0.0f;                                       mat[1][1] = 2.0 / (t - b);                      mat[1][2] = 0.0f;                               mat[1][3] = - (t + b) / (t - b);
        mat[2][0] = 0.0f;                                       mat[2][1] = 0.0f;                               mat[2][2] = -2.0 / (far - near);                mat[2][3] = - (far + near) / (far - near);
        mat[3][0] = 0.0f;                                       mat[3][1] = 0.0f;                               mat[3][2] = 0.0f;                               mat[3][3] = 1.0f;
        return 0;
    }

    int EyerMat4x4::SetPerspective(float fov, float aspect, float near, float far)
    {
        mat[0][0] = tan(M_PI / 2.0 - (fov / 2.0)) / aspect;     mat[0][1] = 0.0f;                               mat[0][2] = 0.0f;                               mat[0][3] = 0.0f;
        mat[1][0] = 0.0f;                                       mat[1][1] = tan(M_PI / 2.0 - (fov / 2.0));      mat[1][2] = 0.0f;                               mat[1][3] = 0.0f;
        mat[2][0] = 0.0f;                                       mat[2][1] = 0.0f;                               mat[2][2] = -((far + near) / (far - near));     mat[2][3] = - ((2 * near * far) / (far - near));
        mat[3][0] = 0.0f;                                       mat[3][1] = 0.0f;                               mat[3][2] = -1.0f;                              mat[3][3] = 0.0f;
        return 0;
    }

    int EyerMat4x4::SetRotateX(float a)
    {
        mat[0][0] = 1.0f;                                       mat[0][1] = 0.0f;                               mat[0][2] = 0.0f;                               mat[0][3] = 0.0f;
        mat[1][0] = 0.0f;                                       mat[1][1] = cos(a);                             mat[1][2] = -sin(a);                            mat[1][3] = 0.0f;
        mat[2][0] = 0.0f;                                       mat[2][1] = sin(a);                             mat[2][2] = cos(a);                             mat[2][3] = 0.0f;
        mat[3][0] = 0.0f;                                       mat[3][1] = 0.0f;                               mat[3][2] = 0.0f;                               mat[3][3] = 1.0f;
        return 0;
    }

    int EyerMat4x4::SetRotateY(float a)
    {
        mat[0][0] = cos(a);                                     mat[0][1] = 0.0f;                               mat[0][2] = sin(a);                             mat[0][3] = 0.0f;
        mat[1][0] = 0.0f;                                       mat[1][1] = 1.0f;                               mat[1][2] = 0.0f;                               mat[1][3] = 0.0f;
        mat[2][0] = -sin(a);                                    mat[2][1] = 0.0f;                               mat[2][2] = cos(a);                             mat[2][3] = 0.0f;
        mat[3][0] = 0.0f;                                       mat[3][1] = 0.0f;                               mat[3][2] = 0.0f;                               mat[3][3] = 1.0f;
        return 0;
    }

    int EyerMat4x4::SetRotateZ(float a)
    {
        mat[0][0] = cos(a);                                     mat[0][1] = -sin(a);                            mat[0][2] = 0.0f;                               mat[0][3] = 0.0f;
        mat[1][0] = sin(a);                                     mat[1][1] = cos(a);                             mat[1][2] = 0.0f;                               mat[1][3] = 0.0f;
        mat[2][0] = 0.0f;                                       mat[2][1] = 0.0f;                               mat[2][2] = 1.0f;                               mat[2][3] = 0.0f;
        mat[3][0] = 0.0f;                                       mat[3][1] = 0.0f;                               mat[3][2] = 0.0f;                               mat[3][3] = 1.0f;
        return 0;
    }
}