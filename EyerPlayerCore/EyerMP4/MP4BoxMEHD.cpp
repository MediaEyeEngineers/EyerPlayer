#include "MP4BoxMEHD.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxMEHD::MP4BoxMEHD() : MP4FullBox()
    {
        type = BoxType::MEHD;
    }

    MP4BoxMEHD::~MP4BoxMEHD()
    {

    }

    bool MP4BoxMEHD::operator == (const MP4BoxMEHD & mehd) const
    {
        if(!MP4FullBox::operator==(mehd)){
            return false;
        }

        if(fragment_duration != mehd.fragment_duration){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxMEHD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        if(version == 1){
            stream.WriteBigEndian((uint64_t)fragment_duration);
        }
        else{
            stream.WriteBigEndian((uint32_t)fragment_duration);
        }

        return stream.GetBuffer();
    }

    int MP4BoxMEHD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        if(version == 1){
            fragment_duration = stream.ReadBigEndian_int64(offset);
        }
        else{
            fragment_duration = stream.ReadBigEndian_int32(offset);
        }

        return offset;
    }

    uint64_t MP4BoxMEHD::Get_fragment_duration()
    {
        return fragment_duration;
    }

    int MP4BoxMEHD::Set_fragment_duration(uint64_t _fragment_duration)
    {
        fragment_duration = _fragment_duration;
        return 0;
    }

    int MP4BoxMEHD::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%sfragment_duration: %lld\n", levelStr.str, fragment_duration);

        return 0;
    }

    int MP4BoxMEHD::SetDefaultData()
    {
        fragment_duration = 12345;
        size = Serialize().GetLen();
        return 0;
    }
}