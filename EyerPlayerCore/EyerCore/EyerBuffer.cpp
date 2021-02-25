#include "EyerBuffer.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Eyer{
    EyerBuffer::EyerBuffer()
    {
    }

    EyerBuffer::~EyerBuffer()
    {
        Clear();
    }

    EyerBuffer::EyerBuffer(const EyerBuffer & buffer) : EyerBuffer()
    {
        *this = buffer;
    }

    EyerBuffer & EyerBuffer::operator = (const EyerBuffer & buffer)
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }

        bufLen = buffer.bufLen;

        buf = (unsigned char *)malloc(bufLen);
        memcpy(buf, buffer.buf, bufLen);

        return *this;
    }

    int EyerBuffer::Append(unsigned char * _buf, int _bufLen)
    {
        unsigned char * tempBuf = (unsigned char *)malloc(bufLen + _bufLen);

        memcpy(tempBuf, buf, bufLen);
        memcpy(tempBuf + bufLen, _buf, _bufLen);

        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }

        bufLen = bufLen + _bufLen;
        buf = tempBuf;

        return 0;
    }

    int EyerBuffer::Append(const EyerBuffer & buffer)
    {
        return Append(buffer.buf, buffer.bufLen);
    }

    int EyerBuffer::CutOff(uint8_t * buffer, int len)
    {
        if(len <= 0){
            return 0;
        }

        if(len > bufLen){
            return 0;
        }

        memcpy(buffer, buf, len);

        int distBufLen = bufLen - len;

        unsigned char * tempBuf = (unsigned char *)malloc(distBufLen);
        memcpy(tempBuf, buf + len, distBufLen);

        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }

        bufLen = distBufLen;
        buf = tempBuf;

        return len;
    }

    int EyerBuffer::CutOff(EyerBuffer & buffer, int len)
    {
        if(len <= 0){
            return 0;
        }

        if(len > bufLen){
            return 0;
        }

        buffer.Clear();
        buffer.Append(buf, len);

        int distBufLen = bufLen - len;

        unsigned char * tempBuf = (unsigned char *)malloc(distBufLen);
        memcpy(tempBuf, buf + len, distBufLen);

        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }

        bufLen = distBufLen;
        buf = tempBuf;

        return len;
    }

    int EyerBuffer::GetBuffer(unsigned char * _buf)
    {
        if(_buf == nullptr){
            return bufLen;
        }

        memcpy(_buf, buf, bufLen);

        return 0;
    }

    int EyerBuffer::GetLen()
    {
        return GetBuffer();
    }

    int EyerBuffer::SetLen(int _len)
    {
        bufLen = _len;
        return 0;
    }

    int EyerBuffer::Clear()
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
        bufLen = 0;
        return 0;
    }

    int EyerBuffer::WriteDisk(EyerString & path)
    {
        FILE * f = fopen(path.str, "wb");
        if(f == nullptr){
            return -1;
        }

        fwrite(buf, bufLen, 1, f);

        fclose(f);

        return 0;
    }

    int EyerBuffer::ReadFromDisk(EyerString & path)
    {
        FILE * f = fopen(path.str, "rb");
        if(f == nullptr){
            return -1;
        }
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
        bufLen = 0;

        fseek(f, 0L, SEEK_END);
        bufLen = ftell(f);

        fseek(f, 0L, SEEK_SET);

        buf = (unsigned char *)malloc(bufLen);
        fread(buf, bufLen, 1, f);

        fclose(f);
        return 0;
    }

    unsigned char * EyerBuffer::GetPtr()
    {
        return buf;
    }
}
