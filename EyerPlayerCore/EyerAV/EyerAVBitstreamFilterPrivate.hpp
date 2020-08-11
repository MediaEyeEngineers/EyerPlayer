//
// Created by lichi on 2020/8/11.
//

#ifndef EYE_LIB_EYERAVBITSTREAMFILTERPRIVATE_HPP
#define EYE_LIB_EYERAVBITSTREAMFILTERPRIVATE_HPP

extern "C" {
#include <libavcodec/avcodec.h>
}

namespace Eyer
{
    class EyerAVBitstreamFilterPrivate {
    public:
        AVBitStreamFilterContext * h264bsfc = nullptr;
    };
}

#endif //EYE_LIB_EYERAVBITSTREAMFILTERPRIVATE_HPP
