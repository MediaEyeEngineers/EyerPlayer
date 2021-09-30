#include "EyerNALUnitSEI.hpp"
#include "EyerAVC/EyerBitStream.hpp"

namespace Eyer
{
    EyerNALUnitSEI::EyerNALUnitSEI(uint8_t * _buf, int _bufLen, int _startCodeLen)
        : EyerNALUnit(_buf, _bufLen, _startCodeLen)
    {

    }

    EyerNALUnitSEI::~EyerNALUnitSEI()
    {

    }

    int EyerNALUnitSEI::Parse()
    {
        int forbidden_bit   = (*(buf + startCodeLen) >> 7) & 1;
        int nal_ref_idc     = (*(buf + startCodeLen) >> 5) & 3;
        int nal_unit_type   = (*(buf + startCodeLen) >> 0) & 0x1f;

        if(nal_unit_type != 6){
            return -1;
        }

        EyerBitStream bs(buf + 1 + startCodeLen, bufLen - (1 + startCodeLen));

        // Parse Payload Type
        uint8_t payloadType = 0;
        while(bs.bs_peek_u(8) == 0xFF){
            bs.bs_read_u8();
            payloadType += 255;
        }

        int last_payload_type_byte = bs.bs_read_u8();
        payloadType += last_payload_type_byte;

        // Parse Payload Size
        int payloadSize = 0;
        while(bs.bs_peek_u(8) == 0xFF){
            bs.bs_read_u8();
            payloadSize += 255;
        }
        int last_payload_size_byte = bs.bs_read_u8();
        payloadSize += last_payload_size_byte;

        EyerLog("Payload Type: %d\n", payloadType);
        EyerLog("Payload Size: %d\n", payloadSize);

        return 0;
    }
}