#ifndef EYE_LIB_EYERBUFFER_HPP
#define EYE_LIB_EYERBUFFER_HPP

#include <stdint.h>

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

        int Clear();

    private:
        unsigned char * buf = nullptr;
        int bufLen = 0;
    };
}

#endif //EYE_LIB_EYERBUFFER_HPP
