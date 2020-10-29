#include "MP4BoxSTCO.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxSTCO::MP4BoxSTCO() : MP4FullBox()
    {
        type = BoxType::STCO;
    }

    MP4BoxSTCO::~MP4BoxSTCO()
    {
        chunk_offset_list.clear();
    }

    bool MP4BoxSTCO::operator == (const MP4BoxSTCO & stco) const
    {
        if(!MP4FullBox::operator==(stco)){
            return false;
        }

        if(chunk_offset_list.size() != stco.chunk_offset_list.size()){
            return false;
        }

        for(int i=0;i<chunk_offset_list.size();i++){
            if(chunk_offset_list[i] != stco.chunk_offset_list[i]){
                return false;
            }
        }

        return true;
    }

    EyerBuffer MP4BoxSTCO::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        stream.WriteBigEndian((uint32_t)chunk_offset_list.size());
        for(int i=0;i<chunk_offset_list.size();i++){
            stream.WriteBigEndian(chunk_offset_list[i]);
        }

        return stream.GetBuffer();
    }

    int MP4BoxSTCO::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        uint32_t entry_count = stream.ReadBigEndian_uint32(offset);
        for(int i=0;i<entry_count;i++){
            uint32_t chunk_offset = stream.ReadBigEndian_uint32(offset);
            chunk_offset_list.push_back(chunk_offset);
        }

        return offset;
    }

    int MP4BoxSTCO::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        for(int i=0;i<chunk_offset_list.size();i++){
            printf("%schunk_offset: %d\n", levelStr.str, chunk_offset_list[i]);
        }

        return 0;
    }

    int MP4BoxSTCO::SetDefaultData()
    {
        for(int i=0;i<10;i++){
            chunk_offset_list.push_back(i);
        }
        size = Serialize().GetLen();
        return 0;
    }
}