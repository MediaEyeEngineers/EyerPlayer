#include "MP4BoxELST.hpp"

#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxELST::MP4BoxELST() : MP4FullBox()
    {
        type = BoxType::ELST;
    }

    MP4BoxELST::~MP4BoxELST()
    {
        for(int i=0;i<entryList.size();i++){
            delete entryList[i];
        }
        entryList.clear();
    }

    bool MP4BoxELST::operator == (const MP4BoxELST & elst) const
    {
        if(!MP4FullBox::operator==(elst)){
            return false;
        }

        if(entryList.size() != elst.entryList.size()){
            return false;
        }

        for(int i=0;i<entryList.size();i++){
            MP4BoxELSTEntry * entryA = entryList[i];
            MP4BoxELSTEntry * entryB = elst.entryList[i];

            if(entryA->media_rate != entryB->media_rate){
                return false;
            }
            if(entryA->media_time != entryB->media_time){
                return false;
            }
            if(entryA->segment_duration != entryB->segment_duration){
                return false;
            }
        }

        return true;
    }

    EyerBuffer MP4BoxELST::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        uint32_t entry_count = entryList.size();
        stream.WriteBigEndian(entry_count);

        for(int i=0;i<entry_count;i++){
            if(version == 1){
                uint64_t segment_duration = entryList[i]->segment_duration;
                int64_t media_time = entryList[i]->media_time;
                stream.WriteBigEndian(segment_duration);
                stream.WriteBigEndian(media_time);
            }
            else {
                uint64_t segment_duration = entryList[i]->segment_duration;
                int64_t media_time = entryList[i]->media_time;
                stream.WriteBigEndian((uint32_t)segment_duration);
                stream.WriteBigEndian((int32_t)media_time);
            }

            stream.WriteBigEndianFixedPoint(entryList[i]->media_rate, 16, 16);
        }

        return stream.GetBuffer();
    }

    int MP4BoxELST::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        uint32_t entry_count = stream.ReadBigEndian_uint32(offset);
        for(int i=0;i<entry_count;i++){
            MP4BoxELSTEntry * entry = new MP4BoxELSTEntry();
            if(version == 1){
                uint64_t    segment_duration    = stream.ReadBigEndian_uint64(offset);
                int64_t     media_time          = stream.ReadBigEndian_int64(offset);

                entry->segment_duration = segment_duration;
                entry->media_time = media_time;
            }
            else{
                uint32_t    segment_duration    = stream.ReadBigEndian_uint32(offset);
                int32_t     media_time          = stream.ReadBigEndian_int32(offset);

                entry->segment_duration = segment_duration;
                entry->media_time = media_time;
            }

            float media_rate = stream.ReadBigEndianFixedPoint(16, 16, offset);
            entry->media_rate = media_rate;

            entryList.push_back(entry);
        }

        return offset;
    }

    int MP4BoxELST::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);
        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        for(int i=0;i<entryList.size();i++){
            MP4BoxELSTEntry * entry = entryList[i];
            // printf("%s================\n", levelStr.str);
            printf("%ssegment_duration: %lld\n", levelStr.str, entry->segment_duration);
            printf("%smedia_time: %lld\n", levelStr.str, entry->media_time);
            printf("%smedia_rate: %f\n", levelStr.str, entry->media_rate);
        }

        return 0;
    }

    int MP4BoxELST::SetDefaultData()
    {
        version = 0;

        uint32_t entry_count = 10;
        for(int i=0;i<entry_count;i++){
            MP4BoxELSTEntry * entry = new MP4BoxELSTEntry();
            entry->segment_duration = i;
            entry->media_rate = i * 10.0;
            entry->media_time = i * -1;
            entryList.push_back(entry);
        }

        type = BoxType::ELST;
        size = Serialize().GetLen();

        return 0;
    }
}
