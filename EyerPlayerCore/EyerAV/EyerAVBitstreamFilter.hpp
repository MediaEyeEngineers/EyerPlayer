#ifndef EYE_LIB_EYERAVBITSTREAMFILTER_HPP
#define EYE_LIB_EYERAVBITSTREAMFILTER_HPP

#include "EyerAVAV.hpp"

namespace Eyer {

    class EyerAVBitstreamFilterPrivate;

    class EyerAVBitstreamFilter {
    public:
        EyerAVBitstreamFilter();
        ~EyerAVBitstreamFilter();

        // int Filter(EyerAVStream & stream, unsigned char * * dstData, int * dstLen, unsigned char * srcData, int srcLen);
        int Filter(EyerAVStream & stream,  EyerAVPacket * pkt, unsigned char * * dstData, int * dstLen);

    private:
        EyerAVBitstreamFilterPrivate * piml = nullptr;
    };
}

#endif //EYE_LIB_EYERAVBITSTREAMFILTER_HPP
