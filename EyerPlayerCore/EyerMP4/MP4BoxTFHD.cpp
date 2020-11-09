//
// Created by Administrator on 2020/11/3.
//
#include "MP4BoxTFHD.hpp"
#include "MP4Stream.hpp"

namespace Eyer{
    MP4BoxTFHD::MP4BoxTFHD(){
        type = BoxType::TFHD;
    }

    MP4BoxTFHD::~MP4BoxTFHD(){

    }

    bool MP4BoxTFHD::operator == (const MP4BoxTFHD & tfhd) const
    {
        if(!MP4FullBox::operator == (tfhd)){
            return false;
        }
        if(track_ID != tfhd.track_ID){
            return false;
        }
        if(base_data_offset != tfhd.base_data_offset){
            return false;
        }
        if(sample_description_index != tfhd.sample_description_index){
            return false;
        }
        if(default_sample_duration != tfhd.default_sample_duration){
            return false;
        }
        if(default_sample_size != tfhd.default_sample_size){
            return false;
        }
        if(default_sample_flags != tfhd.default_sample_flags){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxTFHD::SerializeParam(){
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);
        stream.WriteBigEndian(track_ID);
        stream.WriteBigEndian(base_data_offset);
        stream.WriteBigEndian(sample_description_index);
        stream.WriteBigEndian(default_sample_duration);
        stream.WriteBigEndian(default_sample_size);
        stream.WriteBigEndian(default_sample_flags);

        return stream.GetBuffer();
    }

    int MP4BoxTFHD::ParseParam(EyerBuffer & buffer, int offset){
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        track_ID                            = stream.ReadBigEndian_uint32(offset);
        base_data_offset                    = stream.ReadBigEndian_int64(offset);
        sample_description_index            = stream.ReadBigEndian_uint32(offset);
        default_sample_duration             = stream.ReadBigEndian_uint32(offset);
        default_sample_size                 = stream.ReadBigEndian_uint32(offset);
        default_sample_flags                = stream.ReadBigEndian_uint32(offset);

        return offset;
    }

    int MP4BoxTFHD::PrintInfo(int level){
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%strack_ID: %d\n", levelStr.str, track_ID);
        printf("%sbase_data_offset: %lld\n", levelStr.str, base_data_offset);
        printf("%ssample_description_index: %d\n", levelStr.str, sample_description_index);
        printf("%sdefault_sample_duration: %d\n", levelStr.str, default_sample_duration);
        printf("%sdefault_sample_size: %d\n", levelStr.str, default_sample_size);
        printf("%sdefault_sample_flags: %d\n", levelStr.str, default_sample_flags);

        return 0;
    }

    int MP4BoxTFHD::SetDefaultData(){
        track_ID = 10;
        base_data_offset = 20;
        sample_description_index = 200000;
        default_sample_duration = 30;
        default_sample_size = 40;
        default_sample_flags = 50;
        size = Serialize().GetLen();

        return 0;
    }
}


