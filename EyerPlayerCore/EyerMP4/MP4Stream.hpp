#ifndef EYERLIB_MP4STREAM_HPP
#define EYERLIB_MP4STREAM_HPP

#include "EyerCore/EyerCore.hpp"
#include "BoxType.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

namespace Eyer
{
    class MP4Stream {
    public:
        MP4Stream(EyerBuffer & buffer);
        ~MP4Stream();

        uint64_t ReadBigEndian_uint64(int & offset);
        uint32_t ReadBigEndian_uint32(int & offset);
        uint16_t ReadBigEndian_uint16(int & offset);
        uint8_t  ReadBigEndian_uint8 (int & offset);

        int64_t ReadBigEndian_int64(int & offset);
        int32_t ReadBigEndian_int32(int & offset);
        int16_t ReadBigEndian_int16(int & offset);

        int GetSizeType(int & size, BoxType & type);

        uint32_t Read_uint32(int & offset);

        int ReadStr(EyerString & str, int len);

        float ReadBigEndianFixedPoint(unsigned int integerLength, unsigned int fractionalLength, int & offset);
        int Skip(int len, int & offset);
        int Skip(int len);

        int WriteBigEndian(uint64_t val);
        int WriteBigEndian(uint32_t val);
        int WriteBigEndian(uint16_t val);
        int WriteBigEndian(uint8_t  val);

        int WriteBigEndian(int64_t val);
        int WriteBigEndian(int32_t val);
        int WriteBigEndian(int16_t val);
        int WriteBigEndian(int8_t  val);

        int WriteString(EyerString & str);

        int WriteZero(int len);

        int WriteBigEndianFixedPoint(float val, unsigned int integerLength, unsigned int fractionalLength);

        EyerBuffer & GetBuffer();
        int CutOff(EyerBuffer & buffer, int len);
    private:
        EyerBuffer buffer;
    };
}



#endif //EYERLIB_MP4STREAM_HPP
