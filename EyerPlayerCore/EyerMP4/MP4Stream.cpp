#include "MP4Stream.hpp"
#include <math.h>
#include <EyerCore/EyerCore.hpp>

namespace Eyer {
    MP4Stream::MP4Stream(EyerBuffer &_buffer) {
        buffer = _buffer;
    }

    MP4Stream::~MP4Stream() {

    }

    uint64_t MP4Stream::ReadBigEndian_uint64(int &offset) {
        uint64_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint64_t));

        offset += sizeof(uint64_t);

        return EyerUtil::EndianNtohll(val_net);
    }

    uint32_t MP4Stream::ReadBigEndian_uint32(int &offset) {
        uint32_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint32_t));

        offset += sizeof(uint32_t);

        return EyerUtil::EndianNtohl(val_net);
    }

    uint16_t MP4Stream::ReadBigEndian_uint16(int &offset) {
        uint16_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint16_t));

        offset += sizeof(uint16_t);

        return EyerUtil::EndianNtohs(val_net);
    }

    int64_t MP4Stream::ReadBigEndian_int64(int & offset)
    {
        int64_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(int64_t));

        offset += sizeof(int64_t);

        return EyerUtil::EndianNtohll(val_net);
    }

    int32_t MP4Stream::ReadBigEndian_int32(int & offset)
    {
        int32_t val_net = Read_uint32(offset);
        return EyerUtil::EndianNtohl(val_net);
    }

    int MP4Stream::GetSizeType(int & size, BoxType & type)
    {
        unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
        buffer.GetBuffer(data);

        uint32_t net_size;
        memcpy(&net_size, data, sizeof(uint32_t));
        size = EyerUtil::EndianNtohl(net_size);

        uint32_t net_type;
        memcpy(&net_type, data + sizeof(uint32_t), 4);
        type = BoxType::GetType(net_type);

        free(data);
        return 0;
    }

    uint32_t MP4Stream::Read_uint32(int & offset)
    {
        int32_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(int32_t));

        offset += sizeof(int32_t);

        return val_net;
    }

    int16_t MP4Stream::ReadBigEndian_int16(int & offset)
    {
        int16_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(int16_t));

        offset += sizeof(int16_t);

        return EyerUtil::EndianNtohs(val_net);
    }

    uint8_t  MP4Stream::ReadBigEndian_uint8 (int & offset)
    {
        uint8_t val_net;
        buffer.CutOff((uint8_t *) &val_net, sizeof(uint8_t));

        offset += sizeof(uint8_t);

        return val_net;
    }

    float MP4Stream::ReadBigEndianFixedPoint(unsigned int integerLength, unsigned int fractionalLength, int &offset) {
        uint32_t n;
        if (integerLength + fractionalLength == 16) {
            n = ReadBigEndian_uint16(offset);
        } else {
            n = ReadBigEndian_uint32(offset);
        }

        unsigned int integer        = n >> fractionalLength;
        unsigned int fractionalMask = pow(2, fractionalLength) - 1;
        float fractional            = (n & fractionalMask) * 1.0 / (1 << fractionalLength);


        return integer + fractional;
    }

    int MP4Stream::ReadStr(EyerString & str, int len)
    {
        char * strBuffer = (char *)malloc(len + 1);
        buffer.CutOff((uint8_t *) strBuffer, len);
        strBuffer[len] = '\0';
        str = strBuffer;

        free(strBuffer);
        return 0;
    }

    int MP4Stream::Skip(int len)
    {
        int offset;
        return Skip(len, offset);
    }

    int MP4Stream::Skip(int len, int & offset)
    {
        EyerBuffer b;
        buffer.CutOff(b, len);

        offset += len;

        return 0;
    }





    int MP4Stream::WriteBigEndian(uint64_t val)
    {
        uint64_t net_val = EyerUtil::EndianHtonll(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint64_t));
        return sizeof(uint64_t);
    }

    int MP4Stream::WriteBigEndian(uint32_t val)
    {
        uint32_t net_val = EyerUtil::EndianHtonl(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint32_t));
        return sizeof(uint32_t);
    }

    int MP4Stream::WriteBigEndian(uint16_t val)
    {
        uint16_t net_val = EyerUtil::EndianHtons(val);
        buffer.Append((uint8_t *)&net_val, sizeof(uint16_t));
        return sizeof(uint16_t);
    }

    int MP4Stream::WriteBigEndian(uint8_t  val)
    {
        buffer.Append((uint8_t *)&val, sizeof(uint8_t));
        return sizeof(uint8_t);
    }



    int MP4Stream::WriteBigEndian(int64_t val)
    {
        int64_t net_val = EyerUtil::EndianHtonll(val);
        buffer.Append((uint8_t *)&net_val, sizeof(int64_t));
        return sizeof(int64_t);
    }

    int MP4Stream::WriteBigEndian(int32_t val)
    {
        int32_t net_val = EyerUtil::EndianHtonl(val);
        buffer.Append((uint8_t *)&net_val, sizeof(int32_t));
        return sizeof(int32_t);
    }

    int MP4Stream::WriteBigEndian(int16_t val)
    {
        int16_t net_val = EyerUtil::EndianHtons(val);
        buffer.Append((uint8_t *)&net_val, sizeof(int16_t));
        return sizeof(int16_t);
    }

    int MP4Stream::WriteBigEndian(int8_t  val)
    {
        buffer.Append((uint8_t *)&val, sizeof(int8_t));
        return sizeof(int8_t);
    }



    int MP4Stream::WriteZero(int len)
    {
        unsigned char * a = (unsigned char *)malloc(len);
        memset(a, 0, len);
        buffer.Append(a, len);
        free(a);
        return len;
    }

    int MP4Stream::WriteString(EyerString & str)
    {
        int len = strlen(str.str) + 1;

        buffer.Append((unsigned char *)str.str, len);

        return len;
    }



    int MP4Stream::WriteBigEndianFixedPoint(float val, unsigned int integerLength, unsigned int fractionalLength)
    {
        if(integerLength == 16 && fractionalLength == 16){
            uint16_t i = (uint16_t)val;
            WriteBigEndian(i);

            float ff = val - i;

            unsigned int fractionalMask = pow(2, fractionalLength) - 1;
            uint16_t f = (uint16_t)(ff * fractionalMask);
            WriteBigEndian(f);
        }

        if(integerLength == 8 && fractionalLength == 8){
            uint8_t i = (uint8_t)val;
            WriteBigEndian(i);

            float ff = val - i;

            unsigned int fractionalMask = pow(2, fractionalLength) - 1;
            uint8_t f = (uint8_t)(ff * fractionalMask);
            WriteBigEndian(f);
        }

        return sizeof(uint32_t);
    }

    EyerBuffer & MP4Stream::GetBuffer()
    {
        return buffer;
    }

    int MP4Stream::CutOff(EyerBuffer & buf, int len)
    {
        return buffer.CutOff(buf, len);
    }
}