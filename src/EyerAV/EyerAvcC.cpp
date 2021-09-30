#include "EyerAvcC.hpp"
#include "EyerAVC/EyerAVC.hpp"

namespace Eyer
{
    EyerAvcC::EyerAvcC()
    {

    }

    EyerAvcC::~EyerAvcC()
    {

    }

    int EyerAvcC::Parse(uint8_t * buf, int len)
    {
        EyerBitStream bitStream(buf, len);
        version             = bitStream.bs_read_u8();
        avc_profile         = bitStream.bs_read_u8();
        avc_compatibility   = bitStream.bs_read_u8();
        avc_level           = bitStream.bs_read_u8();
        bitStream.bs_skip_u(6);
        NALULengthSizeMinusOne = bitStream.bs_read_u(2);

        EyerLog("version: %d\n",            version);
        EyerLog("avc_profile: %d\n",        avc_profile);
        EyerLog("avc_compatibility: %d\n",  avc_compatibility);
        EyerLog("avc_level: %d\n",          avc_level);

        EyerLog("NALULengthSizeMinusOne: %d\n",          NALULengthSizeMinusOne);


        return 0;
    }

    int EyerAvcC::GetNALULengthSize()
    {
        return NALULengthSizeMinusOne + 1;
    }
}