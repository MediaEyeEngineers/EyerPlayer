#include "EyerAnnexBParse.hpp"

#include "EyerCore/EyerCore.hpp"
#include "EyerAVFFmpegHeader.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVReaderPrivate.hpp"
#include "EyerNALUnit.hpp"
#include "EyerNALUnitSEI.hpp"

namespace Eyer
{
    EyerAnnexBParse::EyerAnnexBParse()
    {

    }

    EyerAnnexBParse::~EyerAnnexBParse()
    {

    }

    int EyerAnnexBParse::Parse(EyerAVPacket & packet)
    {
        uint8_t * data = packet.piml->packet->data;
        int data_size = packet.piml->packet->size;
        // EyerLog("%d, %d, %d, %d, %d\n", data[0], data[1], data[2], data[3], data[4]);

        struct TempNalu
        {
            int start_pos;
            int nalu_type;
            int start_code_len;
        };

        std::vector<struct TempNalu> tempNaluList;

        // 查找 Start Code
        for(int i=0;i<data_size;){
            int startCodeLen = 0;
            bool startCode = CheckStartCode(startCodeLen, data + i, data_size - i);
            if(startCode){
                uint8_t * bufPtr = data + i;
                int forbidden_bit   = (*(bufPtr + startCodeLen) >> 7) & 1;
                int nal_ref_idc     = (*(bufPtr + startCodeLen) >> 5) & 3;
                int nal_unit_type   = (*(bufPtr + startCodeLen) >> 0) & 0x1f;

                struct TempNalu tempNalu;
                tempNalu.start_pos = i;
                tempNalu.nalu_type = nal_unit_type;
                tempNalu.start_code_len = startCodeLen;
                tempNaluList.push_back(std::move(tempNalu));

                i += startCodeLen;
                continue;
            }
            i++;
        }

        int offset = 0;
        for(int i = 0; i < tempNaluList.size(); i++){
            int startPos = tempNaluList[i].start_pos;
            int endPos = data_size;
            if(i < tempNaluList.size() - 1){
                endPos = tempNaluList[i + 1].start_pos;
            }

            int naluLen = endPos - startPos;
            // EyerNALUnit nalu(data + offset, naluLen);

            if(tempNaluList[i].nalu_type == 6){
                EyerNALUnitSEI naluSEI(data + offset, naluLen, tempNaluList[i].start_code_len);
                naluSEI.Parse();
            }

            offset += naluLen;
        }

        return 0;
    }

    bool EyerAnnexBParse::CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen)
    {
        if(bufLen <= 2){
            startCodeLen = 0;
            return false;
        }
        if(bufLen >= 4){
            if(bufPtr[0] == 0 && bufPtr[1] == 0) {
                if (bufPtr[2] == 0) {
                    if (bufPtr[3] == 1) {
                        startCodeLen = 4;
                        return true;
                    }
                }
                if(bufPtr[2] == 1){
                    startCodeLen = 3;
                    return true;
                }
            }
        }
        if(bufLen <= 3){
            if(bufPtr[0] == 0 && bufPtr[1] == 0 && bufPtr[2] == 1) {
                startCodeLen = 3;
                return true;
            }
        }

        startCodeLen = 0;
        return false;
    }
}