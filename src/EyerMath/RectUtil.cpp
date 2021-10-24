//
// Created by yao on 2021/6/6.
//

#include "RectUtil.hpp"

namespace Eyer
{
    EectorF4 RectUtil::OverlapRect(Eatrix4x1<float> rectA, Eatrix4x1<float> rectB) {
        EectorF4 ret = EectorF4(0, 0, 0, 0);
        if(rectA.w() == 0 || rectA.z() == 0 || rectB.w() == 0 || rectB.z() == 0){
            return ret;
        }

        //p1：rectA左下角  p2：rectA右上角 p3：rectB左下角  p4：rectB右上角
        //EectorF4的x代表左上角x， y代表左上角y，z代表矩形的宽，w代表矩形的高
        float p1_x = rectA.x();
        float p1_y = rectA.y() + rectA.w();

        float p2_x = rectA.x() + rectA.z();
        float p2_y = rectA.y();

        float p3_x = rectB.x();
        float p3_y = rectB.y() + rectB.w();

        float p4_x = rectB.x() + rectB.z();
        float p4_y = rectB.y();

        if (p1_x >= p4_x || p2_x <= p3_x || p1_y <= p4_y || p2_y >= p3_y) {
            return ret;
        }

        float width = std::min(p2_x, p4_x) - std::max(p1_x, p3_x);
        float height = std::min(p1_y, p3_y) - std::max(p2_y, p4_y);

        float retLeftTop_x = std::max(p1_x, p3_x);
        float retLeftTop_y = std::max(p2_y, p4_y);

        ret.SetX(retLeftTop_x);
        ret.SetY(retLeftTop_y);
        ret.SetZ(width);
        ret.SetW(height);
        return ret;
    }

    bool RectUtil::PointInRect(Eatrix4x1<float> rect, Eatrix4x1<float> point)
    {
        float rightBottom_x = rect.x() + rect.z();
        float rightBottom_y = rect.y() + rect.w();
        if(point.x() >= rect.x() && point.x() <= rightBottom_x && point.y() >= rect.y() && point.y() <= rightBottom_y){
            return true;
        } else{
            return false;
        }
    }

    bool RectUtil::PointXCrossRect(Eatrix4x1<float> rect, Eatrix4x1<float> point)
    {
        float rightBottom_x = rect.x() + rect.z();
        float rightBottom_y = rect.y() + rect.w();
        if(point.y() >= rect.y() && point.y() <= rightBottom_y){
            return true;
        } else{
            return false;
        }
    }


}