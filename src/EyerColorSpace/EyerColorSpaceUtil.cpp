#include "EyerColorSpaceUtil.hpp"

namespace Eyer
{
    float yuv_2_rgb_bt601[] = {
            1,      0,          1.4017,
            1,      -0.3437,    -0.7142,
            1,      1.7722,     0
    };
    EatrixF3x3 EyerColorSpaceUtil::YUV_2_RGB_BT601(yuv_2_rgb_bt601);

    float yuv_2_rgb_bt709[] = {
            1,      0,          1.5748,
            1,      -0.1873,    -0.4681,
            1,      1.8556,     0
    };
    EatrixF3x3 EyerColorSpaceUtil::YUV_2_RGB_BT709(yuv_2_rgb_bt709);

    float yuv_2_rgb_bt2020[] = {
            1,              0,                      1.4746,
            1,              -0.16455312684366,      -0.57135312684366,
            1,              1.8814,                 0
    };
    EatrixF3x3 EyerColorSpaceUtil::YUV_2_RGB_BT2020(yuv_2_rgb_bt2020);



    float rgb_2_xyz_bt709[] = {
            0.4124,         0.3576,             0.1805,
            0.2126,         0.7152,             0.0722,
            0.0193,         0.1192,             0.9505
    };
    EatrixF3x3 EyerColorSpaceUtil::RGB_2_XYZ_BT709(rgb_2_xyz_bt709);


    float rgb_2_xyz_bt2020[] = {
            0.6370,         0.1446,             0.1689,
            0.2627,         0.6780,             0.0593,
            0,              0.0281,             1.0610
    };
    EatrixF3x3 EyerColorSpaceUtil::RGB_2_XYZ_BT2020(yuv_2_rgb_bt2020);


    float rgb_2_xyz_srgb[] = {
            0.4124, 0.3576, 0.1805,
            0.2126, 0.7152, 0.0722,
            0.0193, 0.1192, 0.9505
    };
    EatrixF3x3 EyerColorSpaceUtil::RGB_2_XYZ_sRGB(rgb_2_xyz_srgb);

    float rgb_2_xyz_adobergb[] = {
            0.57667, 0.18555, 0.18819,
            0.29738, 0.62735, 0.07527,
            0.02703, 0.07069, 0.99110
    };
    EatrixF3x3 EyerColorSpaceUtil::RGB_2_XYZ_AdobeRGB(rgb_2_xyz_adobergb);

    float rgb_2_xyz_dcip3[] = {
            0.4866, 0.2657, 0.1982,
            0.2290, 0.6917, 0.0793,
            0, 0.0451, 1.0439
    };
    EatrixF3x3 EyerColorSpaceUtil::RGB_2_XYZ_DCI_P3(rgb_2_xyz_dcip3);


    int EyerColorSpaceUtil::AddEatrix(const EatrixF3x3 & transformMat)
    {
        transformEatrixVec.push_back(transformMat);
        return 0;
    }

    const EatrixF3x3 EyerColorSpaceUtil::GetMat()
    {
        EatrixF3x3 m;
        for (int i = 0; i < transformEatrixVec.size(); i++) {
            m = transformEatrixVec[i] * m;
        }
        return m;
    }
}