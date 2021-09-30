#ifndef EYERLIB_EYERNALUNITSEI_HPP
#define EYERLIB_EYERNALUNITSEI_HPP

#include "EyerNALUnit.hpp"

namespace Eyer {

    class EyerNALUnitSEI : public EyerNALUnit
    {
    public:
        EyerNALUnitSEI(uint8_t * _buf, int _bufLen, int _startCodeLen);
        ~EyerNALUnitSEI();

        int Parse() override;
    };
}

#endif //EYERLIB_EYERNALUNITSEI_HPP
