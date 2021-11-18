#ifndef EYERLIB_EYERCOLORSPACE_H
#define EYERLIB_EYERCOLORSPACE_H

#include <iostream>
#include <cstdio>
#include <EyerMath/EyerMath.hpp>

namespace Eyer
{
    class EyerColorSpace
    {
    public:
        EyerColorSpace();
        ~EyerColorSpace();

        int AddEatrix(const Eyer::Eatrix<float> & transformMat);
        Eyer::EectorF3 Convert(Eyer::EectorF3 rgb);

        int GetMat(Eyer::Eatrix<float> & mat);
    private:
        std::vector<Eyer::Eatrix<float>> transformEatrixVec;

    };

    class EyerColorSpaceMat
    {
    private:
        EyerColorSpaceMat();
    public:
        static EyerColorSpaceMat * instance;
        static EyerColorSpaceMat * GetInstance();

        Eyer::Eatrix<float> rgb2020_xyz_mat;
        Eyer::Eatrix<float> rgb709_xyz_mat;
        Eyer::Eatrix<float> sRGB_xyz_mat;
        Eyer::Eatrix<float> adobeRGB_xyz_mat;
        Eyer::Eatrix<float> DCI_P3_xyz_mat;

        //yuv范围(0,255)  bt601和bt709的 yuv 转 rgb 矩阵一样
        Eyer::Eatrix<float> yuv601_rgb601_255_mat;
        Eyer::Eatrix<float> yuv709_rgb709_255_mat;
        //yuv范围(0,255)
        Eyer::Eatrix<float> yuv2020_rgb2020_255_mat;

    };

}
#endif //EYERLIB_EYERCOLORSPACE_H
