#include "MP4BoxMFHD.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxMFHD::MP4BoxMFHD() : MP4FullBox()
    {
        type = BoxType::MFHD;
    }

    MP4BoxMFHD::~MP4BoxMFHD()
    {

    }

    bool MP4BoxMFHD::operator == (const MP4BoxMFHD & mfhd) const
    {
        if(!MP4FullBox::operator==(mfhd)){
            return false;
        }

        if(sequence_number != mfhd.sequence_number){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxMFHD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        stream.WriteBigEndian((uint32_t)sequence_number);

        return stream.GetBuffer();
    }

    int MP4BoxMFHD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        sequence_number = stream.ReadBigEndian_int32(offset);

        return offset;
    }

    uint32_t MP4BoxMFHD::Get_sequence_number()
    {
        return sequence_number;
    }

    int MP4BoxMFHD::Set_sequence_number(uint32_t _sequence_number)
    {
        sequence_number = _sequence_number;
        return 0;
    }

    int MP4BoxMFHD::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%ssequence_number: %lld\n", levelStr.str, sequence_number);

        return 0;
    }

    int MP4BoxMFHD::SetDefaultData()
    {
        sequence_number = 12345;
        size = Serialize().GetLen();
        return 0;
    }
}