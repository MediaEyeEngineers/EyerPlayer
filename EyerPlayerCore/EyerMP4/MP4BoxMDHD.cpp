#include "MP4BoxMDHD.hpp"
#include "MP4Stream.hpp"

namespace Eyer {
    MP4BoxMDHD::MP4BoxMDHD() : MP4FullBox()
    {
        type = BoxType::MDHD;
    }

    MP4BoxMDHD::~MP4BoxMDHD()
    {

    }

    bool MP4BoxMDHD::operator == (const MP4BoxMDHD & mdhd) const
    {
        if(!MP4FullBox::operator==(mdhd)){
            return false;
        }

        if(creation_time != mdhd.creation_time){
            return false;
        }
        if(modification_time != mdhd.modification_time){
            return false;
        }
        if(time_scale != mdhd.time_scale){
            return false;
        }
        if(duration != mdhd.duration){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxMDHD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        if(version == 1){
            stream.WriteBigEndian((uint64_t)creation_time);
            stream.WriteBigEndian((uint64_t)modification_time);
            stream.WriteBigEndian((uint32_t)time_scale);
            stream.WriteBigEndian((uint64_t)duration);
        }
        else{
            stream.WriteBigEndian((uint32_t)creation_time);
            stream.WriteBigEndian((uint32_t)modification_time);
            stream.WriteBigEndian((uint32_t)time_scale);
            stream.WriteBigEndian((uint32_t)duration);
        }

        stream.WriteZero(sizeof(uint16_t));
        stream.WriteZero(sizeof(uint16_t));

        return stream.GetBuffer();
    }

    int MP4BoxMDHD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        if(version == 1){
            creation_time           = (uint64_t)stream.ReadBigEndian_uint64(offset);
            modification_time       = (uint64_t)stream.ReadBigEndian_uint64(offset);
            time_scale              = (uint32_t)stream.ReadBigEndian_uint32(offset);
            duration                = (uint64_t)stream.ReadBigEndian_uint64(offset);
        }
        else{
            creation_time           = (uint32_t)stream.ReadBigEndian_uint32(offset);
            modification_time       = (uint32_t)stream.ReadBigEndian_uint32(offset);
            time_scale              = (uint32_t)stream.ReadBigEndian_uint32(offset);
            duration                = (uint32_t)stream.ReadBigEndian_uint32(offset);
        }

        stream.Skip(sizeof(uint16_t), offset);
        stream.Skip(sizeof(uint16_t), offset);

        return offset;
    }

    int MP4BoxMDHD::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%screation_time: %lld\n", levelStr.str, creation_time);
        printf("%smodification_time: %lld\n", levelStr.str, modification_time);
        printf("%stime_scale: %d\n", levelStr.str, time_scale);
        printf("%sduration: %lld\n", levelStr.str, duration);

        return 0;
    }

    int MP4BoxMDHD::SetDefaultData()
    {
        return 0;
    }
}