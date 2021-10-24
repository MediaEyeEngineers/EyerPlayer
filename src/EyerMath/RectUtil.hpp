//
// Created by yao on 2021/6/6.
//

#ifndef EYERLIB_RECTUTIL_HPP
#define EYERLIB_RECTUTIL_HPP

#include "EyerMath.hpp"

namespace Eyer
{
    class RectUtil {
    public:
        /**
         * 计算两个矩形重叠的矩形
         * @param rectA 矩形A EectorF4的x代表左上角x， y代表左上角y，z代表矩形的宽，w代表矩形的高
         * @param rectB 同上
         * @return 返回EectorF4，x代表左上角x， y代表左上角y，z代表矩形的宽，w代表矩形的高
         */
        Eatrix4x1<float> OverlapRect(Eatrix4x1<float> rectA, Eatrix4x1<float> rectB);

        /**
         * 判断点是否在矩形中
         * @param rect 矩形, EectorF4，x代表左上角x， y代表左上角y，z代表矩形的宽，w代表矩形的高
         * @param point 点
         * @return true代表在矩形中
         */
        bool PointInRect(Eatrix4x1<float> rect, Eatrix4x1<float> point);

        /**
        * 判断点是否在矩形中且横向贯穿矩形
        * @param rect 矩形, EectorF4，x代表左上角x， y代表左上角y，z代表矩形的宽，w代表矩形的高
        * @param point 点
        * @return true代表在矩形中
        */
        bool PointXCrossRect(Eatrix4x1<float> rect, Eatrix4x1<float> point);
    };
}

#endif //EYERLIB_RECTUTIL_HPP
