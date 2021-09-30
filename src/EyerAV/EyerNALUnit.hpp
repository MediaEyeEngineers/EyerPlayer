#ifndef EYERLIB_EYERNALUNIT_HPP
#define EYERLIB_EYERNALUNIT_HPP

#include <stdint.h>

namespace Eyer
{
    class EyerNALUnit
    {
    public:
        EyerNALUnit(uint8_t * _buf, int _bufLen, int _startCodeLen);
        virtual ~EyerNALUnit();

        virtual int Parse();

    protected:
        uint8_t * buf = nullptr;
        int bufLen = 0;
        int startCodeLen = 0;

    private:

    };
}

#endif //EYERLIB_EYERNALUNIT_HPP
