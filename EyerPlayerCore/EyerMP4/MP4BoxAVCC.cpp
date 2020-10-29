#include "MP4BoxAVCC.hpp"
#include "MP4Stream.hpp"


namespace Eyer
{
    MP4BoxAVCC::MP4BoxAVCC() : MP4Box()
    {
        type = BoxType::AVCC;
    }

    MP4BoxAVCC::~MP4BoxAVCC()
    {
        for(int i=0; i<spsList.size(); i++){
            delete spsList[i];
        }
        spsList.clear();

        for(int i=0; i<ppsList.size(); i++){
            delete ppsList[i];
        }
        ppsList.clear();

        for(int i=0; i<spsExtList.size(); i++){
            delete spsExtList[i];
        }
        spsExtList.clear();
    }

    bool MP4BoxAVCC::operator == (const MP4BoxAVCC & avcc) const
    {
        if(!MP4Box::operator==(avcc)){
            return false;
        }
        return true;
    }

    EyerBuffer MP4BoxAVCC::SerializeParam()
    {
        EyerBuffer buffer;
        MP4Stream stream(buffer);

        return stream.GetBuffer();
    }

    int MP4BoxAVCC::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4Box::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        configurationVersion    = stream.ReadBigEndian_uint8(offset);
        AVCProfileIndication    = stream.ReadBigEndian_uint8(offset);
        profile_compatibility   = stream.ReadBigEndian_uint8(offset);
        AVCLevelIndication      = stream.ReadBigEndian_uint8(offset);

        /*
         * bit(6) reserved = ‘111111’b;
         * unsigned int(2) lengthSizeMinusOne;
         */
        lengthSizeMinusOne      = stream.ReadBigEndian_uint8(offset);
        lengthSizeMinusOne      = lengthSizeMinusOne & 0x3;

        /*
         * bit(3) reserved = ‘111’b;
         * unsigned int(5) numOfSequenceParameterSets; //SPS数据个数
         */
        uint8_t numOfSequenceParameterSets = 0;
        numOfSequenceParameterSets = stream.ReadBigEndian_uint8(offset);
        numOfSequenceParameterSets = numOfSequenceParameterSets & 0x1F;
        /*
        for (i=0; i< numOfSequenceParameterSets; i++) {
            unsigned int(16) sequenceParameterSetLength ;//一个SPS数据内容长度
            bit(8*sequenceParameterSetLength) sequenceParameterSetNALUnit; //一个SPS数据内容
        }
         */
        for(int i=0; i<numOfSequenceParameterSets; i++){
            uint16_t sequenceParameterSetLength = stream.ReadBigEndian_uint16(offset);
            EyerBuffer * sps = new EyerBuffer();
            stream.CutOff(*sps, sequenceParameterSetLength);
            spsList.push_back(sps);
        }

        uint8_t numOfPictureParameterSets = 0;
        numOfPictureParameterSets = stream.ReadBigEndian_uint8(offset);
        for(int i=0; i<numOfPictureParameterSets; i++){
            uint16_t pictureParameterSetLength = stream.ReadBigEndian_uint16(offset);
            EyerBuffer * pps = new EyerBuffer();
            stream.CutOff(*pps, pictureParameterSetLength);
            ppsList.push_back(pps);
        }

        uint8_t profile_idc = AVCProfileIndication;
        // printf("Size: %d\n", stream.GetBuffer().GetLen());
        if(profile_idc == 100 || profile_idc == 110 || profile_idc == 122 || profile_idc == 144)
        {
            /*
             * bit(6) reserved = ‘111111’b;
             * unsigned int(2) chroma_format;
             */
            chroma_format = stream.ReadBigEndian_uint8(offset);
            chroma_format = chroma_format & 0x3;

            /*
             * bit(5) reserved = ‘11111’b;
             * unsigned int(3) bit_depth_luma_minus8;
             */
            bit_depth_luma_minus8 = stream.ReadBigEndian_uint8(offset);
            bit_depth_luma_minus8 = bit_depth_luma_minus8 & 0x7;

            /*
             * bit(5) reserved = ‘11111’b;
             * unsigned int(3) bit_depth_chroma_minus8;
             */
            bit_depth_chroma_minus8 = stream.ReadBigEndian_uint8(offset);
            bit_depth_chroma_minus8 = bit_depth_chroma_minus8 & 0x7;
        }

        uint8_t numOfSequenceParameterSetExt = stream.ReadBigEndian_uint8(offset);
        for (int i=0; i< numOfSequenceParameterSetExt; i++) {
            uint16_t sequenceParameterSetExtLength = stream.ReadBigEndian_uint16(offset);

            EyerBuffer * spsExt = new EyerBuffer();
            stream.CutOff(*spsExt, sequenceParameterSetExtLength);
            spsExtList.push_back(spsExt);
        }
        return offset;
    }

    int MP4BoxAVCC::PrintInfo(int level)
    {
        MP4Box::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%sconfigurationVersion: %d\n", levelStr.str, configurationVersion);
        printf("%sAVCProfileIndication: %d\n", levelStr.str, AVCProfileIndication);
        printf("%sprofile_compatibility: %d\n", levelStr.str, profile_compatibility);
        printf("%sAVCLevelIndication: %d\n", levelStr.str, AVCLevelIndication);
        printf("%slengthSizeMinusOne: %d\n", levelStr.str, lengthSizeMinusOne);

        for(int i=0; i<spsList.size(); i++){
            printf("%ssps len: %d\n", levelStr.str, spsList[i]->GetLen());
        }
        for(int i=0; i<ppsList.size(); i++){
            printf("%spps len: %d\n", levelStr.str, ppsList[i]->GetLen());
        }

        printf("%schroma_format: %d\n",                 levelStr.str, chroma_format);
        printf("%sbit_depth_luma_minus8: %d\n",         levelStr.str, bit_depth_luma_minus8);
        printf("%sbit_depth_chroma_minus8: %d\n",       levelStr.str, bit_depth_chroma_minus8);

        for(int i=0; i<spsExtList.size(); i++){
            printf("%sspsExt len: %d\n", levelStr.str, spsExtList[i]->GetLen());
        }

        return 0;
    }

    int MP4BoxAVCC::SetDefaultData()
    {
        return 0;
    }
}