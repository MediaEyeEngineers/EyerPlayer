#include "EyerColorSpace.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer {

    EyerColorSpace::EyerColorSpace() {

    }

    EyerColorSpace::~EyerColorSpace() {
        transformEatrixVec.clear();
    }

    int EyerColorSpace::AddEatrix(const Eyer::Eatrix<float> &transformMat) {
        transformEatrixVec.push_back(transformMat);
        return 0;
    }

    Eyer::EectorF3 EyerColorSpace::Convert(Eyer::EectorF3 rgb) {
        Eyer::EectorF3 outRgb = rgb;
        for (int i = 0; i < transformEatrixVec.size(); i++) {
            transformEatrixVec[i].PrintInfo();
            outRgb = transformEatrixVec[i] * outRgb;
        }
        return outRgb;
    }

    int EyerColorSpace::GetMat(Eyer::Eatrix<float> & mat)
    {
        Eyer::Eatrix<float> m(3, 3);
        for (int i = 0; i < transformEatrixVec.size(); i++) {
            m = transformEatrixVec[i] * m;
        }
        mat = m;
        return 0;
    }
}