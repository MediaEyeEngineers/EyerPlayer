#include "MP4BoxAVC1.hpp"
#include "MP4Stream.hpp"
#include "MP4BoxAVCC.hpp"

namespace Eyer
{
    MP4BoxAVC1::MP4BoxAVC1() : MP4BoxSampleEntry()
    {
        type = BoxType::AVC1;
    }

    MP4BoxAVC1::~MP4BoxAVC1()
    {

    }

    bool MP4BoxAVC1::operator == (const MP4BoxAVC1 & avc1) const
    {
        if(!MP4Box::operator==(avc1)){
            return false;
        }
        return true;
    }

    EyerBuffer MP4BoxAVC1::SerializeParam()
    {
        EyerBuffer buffer;
        MP4Stream stream(buffer);

        return stream.GetBuffer();
    }

    int MP4BoxAVC1::ParseParam(EyerBuffer & buffer, int offset)
    {
        // https://www.cnblogs.com/lidabo/p/3754130.html
        offset = MP4Box::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        stream.Skip(6 * sizeof(uint8_t), offset);

        data_reference_index = stream.ReadBigEndian_uint16(offset);

        stream.Skip(sizeof(uint16_t), offset);
        stream.Skip(sizeof(uint16_t), offset);
        stream.Skip(sizeof(uint32_t) * 3, offset);

        width = stream.ReadBigEndian_uint16(offset);
        height = stream.ReadBigEndian_uint16(offset);

        horizresolution = stream.ReadBigEndian_uint32(offset);
        vertresolution = stream.ReadBigEndian_uint32(offset);

        stream.Skip(sizeof(uint32_t), offset);

        frame_count = stream.ReadBigEndian_int16(offset);

        stream.ReadStr(compressorname, 32);
        offset += 32;

        depth = stream.ReadBigEndian_uint16(offset);

        stream.Skip(sizeof(uint16_t), offset);


        avcc.Parse(stream.GetBuffer());

        return offset;
    }

    int MP4BoxAVC1::PrintInfo(int level)
    {
        MP4Box::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%sdata_reference_index: %d\n", levelStr.str, data_reference_index);
        printf("%swidth: %d\n", levelStr.str, width);
        printf("%sheight: %d\n", levelStr.str, height);
        printf("%shorizresolution: %d\n", levelStr.str, horizresolution);
        printf("%svertresolution: %d\n", levelStr.str, vertresolution);
        printf("%sframe_count: %d\n", levelStr.str, frame_count);
        printf("%scompressorname: %s\n", levelStr.str, compressorname.str);
        printf("%sdepth: %d\n", levelStr.str, depth);

        avcc.PrintInfo(level + 1);

        return 0;
    }

    int MP4BoxAVC1::SetDefaultData()
    {
        return 0;
    }
}