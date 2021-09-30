#ifndef EYERLIB_EYERAVCSEI_HPP
#define EYERLIB_EYERAVCSEI_HPP

#include "EyerAvcC.hpp"

namespace Eyer
{
    class EyerAVReader;
    class EyerAVPacket;

    class EyerAVCSEI
    {
    public:
        EyerAVCSEI();
        ~EyerAVCSEI();

        int Init(const EyerAVReader & reader);

        int ParseSEI(const EyerAVPacket & packet);

    private:
        EyerAvcC avcC;

        bool CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen);
    };
}

#endif //EYERLIB_EYERAVCSEI_HPP
