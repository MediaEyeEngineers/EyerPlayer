#ifndef EYERLIB_EYERCOLORSPACEUTIL_HPP
#define EYERLIB_EYERCOLORSPACEUTIL_HPP

#include "EyerMath/EyerMath.hpp"

namespace Eyer
{
    class EyerColorSpaceUtil
    {
    public:
        static EatrixF3x3 YUV_2_RGB_BT601;
        static EatrixF3x3 YUV_2_RGB_BT709;
        static EatrixF3x3 YUV_2_RGB_BT2020;

        static EatrixF3x3 RGB_2_XYZ_BT709;
        static EatrixF3x3 RGB_2_XYZ_BT2020;
        static EatrixF3x3 RGB_2_XYZ_sRGB;
        static EatrixF3x3 RGB_2_XYZ_AdobeRGB;
        static EatrixF3x3 RGB_2_XYZ_DCI_P3;

        int AddEatrix(const EatrixF3x3 & transformMat);
        const EatrixF3x3 GetMat();

    private:
        std::vector<EatrixF3x3> transformEatrixVec;
    };
}

#endif //EYERLIB_EYERCOLORSPACEUTIL_HPP