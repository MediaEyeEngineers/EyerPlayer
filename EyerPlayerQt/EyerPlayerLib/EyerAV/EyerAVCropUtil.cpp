#include "EyerAV.hpp"

namespace Eyer
{
    EyerAVCropUtil::EyerAVCropUtil()
    {

    }

    EyerAVCropUtil::~EyerAVCropUtil()
    {

    }

    int EyerAVCropUtil::GetCrop(int viewW, int viewH, int imageW, int imageH, int & targetW, int & targetH, EyerAVCropType cropType)
    {
        if(cropType == EyerAVCropType::FIT_CENTER){
            float viewFit = viewW * 1.0 / viewH;
            float imageFit = imageW * 1.0 / imageH;

            if(viewFit > imageFit){
                // 对高进行限定
                targetH = viewH;
                targetW = imageW * 1.0 / imageH * targetH;
            }
            else{
                targetW = viewW;
                targetH = imageH * 1.0 / imageW * targetW;
            }
        }

        if(cropType == EyerAVCropType::FIT_XY){
            targetW = viewW;
            targetH = viewH;
        }
        return 0;
    }
}