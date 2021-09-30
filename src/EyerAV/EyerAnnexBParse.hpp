#ifndef EYERLIB_EYERANNEXBPARSE_HPP
#define EYERLIB_EYERANNEXBPARSE_HPP

#include "EyerAVPacket.hpp"

namespace Eyer
{
    class EyerAnnexBParse
    {
    public:
        EyerAnnexBParse();
        ~EyerAnnexBParse();

        int Parse(EyerAVPacket & packet);

    protected:

    private:
        bool CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen);
    };
}

#endif //EYERLIB_EYERANNEXBPARSE_HPP
