#include "MP4BoxMVHD.hpp"
#include "EyerISOTypeReader.hpp"

#include "MP4Stream.hpp"


namespace Eyer
{
    MP4BoxMVHD::MP4BoxMVHD() : MP4FullBox()
    {
        type = BoxType::MVHD;
    }

    MP4BoxMVHD::~MP4BoxMVHD()
    {

    }

    bool MP4BoxMVHD::operator == (const MP4BoxMVHD & mvhd) const
    {
        if(!MP4FullBox::operator==(mvhd)){
            return false;
        }

        if(creation_time != mvhd.creation_time){
            return false;
        }
        if(modification_time != mvhd.modification_time){
            return false;
        }
        if(timescale != mvhd.timescale){
            return false;
        }
        if(duration != mvhd.duration){
            return false;
        }
        if(rate != mvhd.rate){
            return false;
        }
        if(volume != mvhd.volume){
            return false;
        }


        return true;
    }

    EyerBuffer MP4BoxMVHD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();

        MP4Stream stream(buffer);

        if(version == 1){
            stream.WriteBigEndian(creation_time);
            stream.WriteBigEndian(modification_time);
            stream.WriteBigEndian(timescale);
            stream.WriteBigEndian(duration);
        }
        else{
            stream.WriteBigEndian((uint32_t)creation_time);
            stream.WriteBigEndian((uint32_t)modification_time);
            stream.WriteBigEndian((uint32_t)timescale);
            stream.WriteBigEndian((uint32_t)duration);
        }

        stream.WriteBigEndianFixedPoint(rate,       16, 16);
        stream.WriteBigEndianFixedPoint(volume,     8,   8);

        stream.WriteZero(2);
        stream.WriteZero(sizeof(uint32_t) * 2);

        for(int i=0;i<9;i++) {
            stream.WriteBigEndianFixedPoint(matrix[i], 16, 16);
        }

        stream.WriteZero(sizeof(uint32_t) * 6);
        stream.WriteBigEndian(next_track_ID);

        return stream.GetBuffer();
    }

    int MP4BoxMVHD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        if(version == 1){
            creation_time       = stream.ReadBigEndian_uint64(offset);
            modification_time   = stream.ReadBigEndian_uint64(offset);
            timescale           = stream.ReadBigEndian_uint32(offset);
            duration            = stream.ReadBigEndian_uint64(offset);
        }
        else{
            creation_time       = stream.ReadBigEndian_uint32(offset);
            modification_time   = stream.ReadBigEndian_uint32(offset);
            timescale           = stream.ReadBigEndian_uint32(offset);
            duration            = stream.ReadBigEndian_uint32(offset);
        }

        rate    = stream.ReadBigEndianFixedPoint(16, 16, offset);
        volume  = stream.ReadBigEndianFixedPoint(8,  8,  offset);

        stream.Skip(2, offset);
        stream.Skip(sizeof(uint32_t) * 2, offset);

        for(int i=0;i<9;i++){
            matrix[i] = stream.ReadBigEndianFixedPoint(16, 16, offset);
        }

        stream.Skip(sizeof(uint32_t) * 6, offset);

        next_track_ID = stream.ReadBigEndian_uint32(offset);

        return offset;
    }

    int MP4BoxMVHD::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%screation_time: %lld\n", levelStr.str, creation_time);
        printf("%smodification_time: %lld\n", levelStr.str, modification_time);
        printf("%stimescale: %d\n", levelStr.str, timescale);
        printf("%sduration: %lld\n", levelStr.str, duration);

        printf("%srate: %f\n", levelStr.str, rate);
        printf("%svolume: %f\n", levelStr.str, volume);

        printf("%s[ %f, %f, %f\n", levelStr.str,  matrix[0], matrix[1], matrix[2]);
        printf("%s  %f, %f, %f\n", levelStr.str,  matrix[3], matrix[4], matrix[5]);
        printf("%s  %f, %f, %f ]\n",levelStr.str, matrix[6], matrix[7], matrix[8]);

        printf("%snext_track_ID: %d\n", levelStr.str, next_track_ID);


        return 0;
    }

    int MP4BoxMVHD::SetDefaultData()
    {
        version = 0;

        creation_time = 123456;
        modification_time = 654321;
        timescale = 1000;
        duration = 6666;

        rate = 2.0f;
        volume = 5.0f;

        matrix[0] = 0.0f; matrix[1] = 1.0f; matrix[2] = 2.0f;
        matrix[3] = 3.0f; matrix[4] = 4.0f; matrix[5] = 5.0f;
        matrix[6] = 6.0f; matrix[7] = 7.0f; matrix[8] = 8.0f;

        next_track_ID = 5;

        type = BoxType::MVHD;
        if(version == 1){
            size = 8 + 8 + 8 + 4 + 8 + 4;
            size += 4 + 2 + 2 + 8 + 9 * 4 + 6 * 4 + 4;
        }
        else{
            size = 8 + 4 + 4 + 4 + 4 + 4;
            size += 4 + 2 + 2 + 8 + 9 * 4 + 6 * 4 + 4;
        }

        return 0;
    }
}