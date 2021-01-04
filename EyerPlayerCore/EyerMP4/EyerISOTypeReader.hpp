#ifndef EYERLIB_EYERISOTYPEREADER_HPP
#define EYERLIB_EYERISOTYPEREADER_HPP

#include <stdint.h>

namespace Eyer
{
    class EyerISOTypeReader {
    public:
        static double ReadFixedPoint1616        (const uint8_t * data);
        static float  ReadFixedPoint88          (const uint8_t * data);
    };
}

#endif //EYERLIB_EYERISOTYPEREADER_HPP
