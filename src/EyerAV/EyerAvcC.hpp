#ifndef EYERLIB_EYERAVCC_HPP
#define EYERLIB_EYERAVCC_HPP

#include <stdint.h>

namespace Eyer
{
    class EyerAvcC
    {
    public:
        EyerAvcC();
        ~EyerAvcC();

        int Parse(uint8_t * buf, int len);

        int GetNALULengthSize();

    private:
        uint8_t version = 0;
        uint8_t avc_profile = 0;
        uint8_t avc_compatibility = 0;
        uint8_t avc_level = 0;

        int NALULengthSizeMinusOne = 0;
    };
}

#endif //EYERLIB_EYERAVCC_HPP
