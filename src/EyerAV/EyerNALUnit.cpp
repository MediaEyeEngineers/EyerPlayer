#include "EyerNALUnit.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerNALUnit::EyerNALUnit(uint8_t * _buf, int _bufLen, int _startCodeLen)
    {
        // 为了安全，这里复制一份出来，后续再进行优化
        bufLen = _bufLen;
        buf = (uint8_t *)malloc(bufLen);
        memcpy(buf, _buf, bufLen);

        startCodeLen = _startCodeLen;

        EyerLog("%d, %d, %d, %d, %d\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
    }

    EyerNALUnit::~EyerNALUnit()
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }

        bufLen = 0;
    }

    int EyerNALUnit::Parse()
    {

        return 0;
    }
}