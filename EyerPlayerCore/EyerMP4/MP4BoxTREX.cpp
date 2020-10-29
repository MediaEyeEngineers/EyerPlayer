#include "MP4BoxTREX.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxTREX::MP4BoxTREX() : MP4FullBox()
    {
        type = BoxType::TREX;
    }

    MP4BoxTREX::~MP4BoxTREX()
    {

    }

    bool MP4BoxTREX::operator == (const MP4BoxTREX & trex) const
    {
        if(!MP4FullBox::operator==(trex)){
            return false;
        }

        if(track_ID != trex.track_ID){
            return false;
        }
        if(default_sample_description_index != trex.default_sample_description_index){
            return false;
        }
        if(default_sample_duration != trex.default_sample_duration){
            return false;
        }
        if(default_sample_size != trex.default_sample_size){
            return false;
        }
        if(default_sample_flag != trex.default_sample_flag){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxTREX::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        stream.WriteBigEndian(track_ID);
        stream.WriteBigEndian(default_sample_description_index);
        stream.WriteBigEndian(default_sample_duration);
        stream.WriteBigEndian(default_sample_size);
        stream.WriteBigEndian(default_sample_flag);

        return stream.GetBuffer();
    }

    int MP4BoxTREX::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        track_ID                            = stream.ReadBigEndian_uint32(offset);
        default_sample_description_index    = stream.ReadBigEndian_uint32(offset);
        default_sample_duration             = stream.ReadBigEndian_uint32(offset);
        default_sample_size                 = stream.ReadBigEndian_uint32(offset);
        default_sample_flag                 = stream.ReadBigEndian_uint32(offset);

        return offset;
    }

    int MP4BoxTREX::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%strack_ID: %d\n", levelStr.str, track_ID);
        printf("%sdefault_sample_description_index: %d\n", levelStr.str, default_sample_description_index);
        printf("%sdefault_sample_duration: %d\n", levelStr.str, default_sample_duration);
        printf("%sdefault_sample_size: %d\n", levelStr.str, default_sample_size);
        printf("%sdefault_sample_flag: %d\n", levelStr.str, default_sample_flag);

        return 0;
    }

    int MP4BoxTREX::SetDefaultData()
    {
        track_ID = 10;
        default_sample_description_index = 20;
        default_sample_duration = 100;
        default_sample_size = 1234;
        default_sample_flag = 12312;

        size = Serialize().GetLen();

        return 0;
    }
}