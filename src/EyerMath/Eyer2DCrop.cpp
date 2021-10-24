#include "Eyer2DCrop.hpp"

namespace Eyer
{
    Eyer2DCrop::Eyer2DCrop(float _canvasWidth, float _canvasHeight)
    {
        canvasWidth = _canvasWidth;
        canvasHeight = _canvasHeight;
    }

    Eyer2DCrop::~Eyer2DCrop()
    {

    }

    Eatrix4x4<float> & Eyer2DCrop::Crop(float viewWidth, float viewHeight, EyerCropType cropType)
    {
        // 缩放坐标系
        ortho.SetOrtho(0.0, canvasWidth, 0.0, canvasHeight, 0.0, 100);

        // 缩放小图
        s.SetScale(0.5, -0.5, 1.0);
        t.SetTrans(1.0, -1.0, 0.0);

        // 进行 Crop
        if(cropType == EyerCropType::FIT_XY){
            scale.SetScale(canvasWidth,  canvasHeight, 1.0);
            trans.SetTrans(0.0, 0.0, 0.0);
        }
        else if(cropType == EyerCropType::FIT_CENTER){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float x = 0.0;
            float y = 0.0;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            if (viewAspect < canvasAspect) {
                targetH = canvasHeight;
                targetW = viewAspect * targetH;
                x = (canvasWidth - targetW) / 2;
            }
            else {
                targetW = canvasWidth;
                targetH = 1.0 / viewAspect * targetW;
                y = (canvasHeight - targetH) / 2;
            }
            scale.SetScale(targetW,  targetH, 1.0);
            trans.SetTrans(x, y, 0.0);
        }

        else if(cropType == EyerCropType::FIT_START){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float x = 0.0;
            float y = 0.0;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            if (viewAspect < canvasAspect) {
                targetH = canvasHeight;
                targetW = viewAspect * targetH;
            }
            else {
                targetW = canvasWidth;
                targetH = 1.0 / viewAspect * targetW;
            }
            scale.SetScale(targetW,  targetH, 1.0);
            trans.SetTrans(x, y, 0.0);
        }

        else if(cropType == EyerCropType::FIT_END){
            float targetW = viewWidth;
            float targetH = viewHeight;

            float x = 0.0;
            float y = 0.0;

            float viewAspect = viewWidth * 1.0 / viewHeight;
            float canvasAspect = canvasWidth * 1.0 / canvasHeight;

            if (viewAspect < canvasAspect) {
                targetH = canvasHeight;
                targetW = viewAspect * targetH;
                x = canvasWidth - targetW;
            }
            else {
                targetW = canvasWidth;
                targetH = 1.0 / viewAspect * targetW;
                y = canvasHeight - targetH;
            }
            scale.SetScale(targetW,  targetH, 1.0);
            trans.SetTrans(x, y, 0.0);
        }

        res = res.Eye() * ortho * trans * scale * s * t;

        return res;
    }
}