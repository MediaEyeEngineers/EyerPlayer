#include "EyerAVCSEI.hpp"

#include "EyerCore/EyerCore.hpp"
#include "EyerAVFFmpegHeader.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVReaderPrivate.hpp"

#include "EyerAVReader.hpp"
#include "EyerAVPacket.hpp"

#include "EyerAvcC.hpp"

#include "EyerAVC/EyerAVC.hpp"

namespace Eyer
{
    EyerAVCSEI::EyerAVCSEI()
    {

    }

    EyerAVCSEI::~EyerAVCSEI()
    {

    }

    int EyerAVCSEI::Init(const EyerAVReader & reader)
    {

        return 0;
    }

    int EyerAVCSEI::ParseSEI(const EyerAVPacket & packet)
    {
        uint8_t * data = packet.piml->packet->data;
        int data_size = packet.piml->packet->size;
        EyerLog("%d, %d, %d, %d, %d\n", data[0], data[1], data[2], data[3], data[4]);

        int lastStartCode = 0;

        int startCodeLen = 0;
        bool startCode = CheckStartCode(startCodeLen, data, data_size);
        if(startCode == false){
            return -1;
        }

        // 查找 Start Code
        for(int i=0;i<data_size;){
            int startCodeLen = 0;
            bool startCode = CheckStartCode(startCodeLen, data + i, data_size - i);
            if(startCode){
                uint8_t * bufPtr = data + i;
                int forbidden_bit   = (*(bufPtr + startCodeLen) >> 7) & 1;
                int nal_ref_idc     = (*(bufPtr + startCodeLen) >> 5) & 3;
                int nal_unit_type   = (*(bufPtr + startCodeLen) >> 0) & 0x1f;
                EyerLog("nal_unit_type: %d\n", nal_unit_type);

                if(nal_unit_type == 6){
                    // EyerBitStream bs();
                }

                i += startCodeLen;
                continue;
            }
            i++;
        }

        return 0;
    }

    bool EyerAVCSEI::CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen)
    {
        if(bufLen <= 2){
            startCodeLen = 0;
            return false;
        }
        if(bufLen >= 4){
            if(bufPtr[0] == 0) {
                if (bufPtr[1] == 0) {
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
        }
        if(bufLen <= 3){
            if(bufPtr[0] == 0) {
                if (bufPtr[1] == 0) {
                    if(bufPtr[2] == 1){
                        startCodeLen = 3;
                        return true;
                    }
                }
            }
        }

        startCodeLen = 0;

        return false;
    }
}