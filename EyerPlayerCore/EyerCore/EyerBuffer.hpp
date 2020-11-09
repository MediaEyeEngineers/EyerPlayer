#ifndef EYE_LIB_EYERBUFFER_HPP
#define EYE_LIB_EYERBUFFER_HPP

#include <stdint.h>
#include <mutex>
#include "EyerString.hpp"

namespace Eyer{
    class EyerBuffer {
    public:
        EyerBuffer();
        ~EyerBuffer();

        EyerBuffer(const EyerBuffer & buffer);
        EyerBuffer & operator = (const EyerBuffer & buffer);

        int Append(unsigned char * _buf, int _bufLen);
        int Append(const EyerBuffer & buffer);

        int CutOff(EyerBuffer & buffer, int len);
        int CutOff(uint8_t * buffer, int len);

        int GetBuffer(unsigned char * _buf = nullptr);

        int GetLen();
        int SetLen(int _len);

        int Clear();

        int WriteDisk(EyerString & path);
        int ReadFromDisk(EyerString & path);


        unsigned char * GetPtr();

    private:
        unsigned char * buf = nullptr;
        int bufLen = 0;
    };
}

#endif //EYE_LIB_EYERBUFFER_HPP
