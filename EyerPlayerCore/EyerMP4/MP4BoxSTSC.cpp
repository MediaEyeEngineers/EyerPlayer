#include "MP4BoxSTSC.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxSTSC::MP4BoxSTSC() : MP4FullBox()
    {
        type = BoxType::STSC;
    }

    MP4BoxSTSC::~MP4BoxSTSC()
    {
        for(int i=0;i<chunkList.size();i++){
            delete chunkList[i];
        }
        chunkList.clear();
    }

    bool MP4BoxSTSC::operator == (const MP4BoxSTSC & stsc) const
    {
        if(!MP4FullBox::operator==(stsc)){
            return false;
        }

        if(chunkList.size() != stsc.chunkList.size()){
            return false;
        }
        for(int i=0;i<chunkList.size();i++) {
            if(chunkList[i]->first_chunk != stsc.chunkList[i]->first_chunk){
                return false;
            }
            if(chunkList[i]->samples_per_chunk != stsc.chunkList[i]->samples_per_chunk){
                return false;
            }
            if(chunkList[i]->sample_description_index != stsc.chunkList[i]->sample_description_index){
                return false;
            }
        }

        return true;
    }

    EyerBuffer MP4BoxSTSC::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        stream.WriteBigEndian((uint32_t)chunkList.size());

        for(int i=0;i<chunkList.size();i++){
            stream.WriteBigEndian(chunkList[i]->first_chunk);
            stream.WriteBigEndian(chunkList[i]->samples_per_chunk);
            stream.WriteBigEndian(chunkList[i]->sample_description_index);
        }

        return stream.GetBuffer();
    }

    int MP4BoxSTSC::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        uint32_t entry_count = stream.ReadBigEndian_uint32(offset);
        for(int i=0;i<entry_count;i++){
            uint32_t first_chunk = stream.ReadBigEndian_uint32(offset);
            uint32_t samples_per_chunk = stream.ReadBigEndian_uint32(offset);
            uint32_t sample_description_index = stream.ReadBigEndian_uint32(offset);

            MP4BoxSTSCChunk * chunk = new MP4BoxSTSCChunk();
            chunk->first_chunk = first_chunk;
            chunk->samples_per_chunk = samples_per_chunk;
            chunk->sample_description_index = sample_description_index;
            chunkList.push_back(chunk);
        }

        return offset;
    }

    int MP4BoxSTSC::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        /*
        for(int i=0;i<chunkList.size();i++){
            printf("%sfirst_chunk: %d\n", levelStr.str, chunkList[i]->first_chunk);
            printf("%ssamples_per_chunk: %d\n", levelStr.str, chunkList[i]->samples_per_chunk);
            printf("%ssample_description_index: %d\n", levelStr.str, chunkList[i]->sample_description_index);
        }
        */

        return 0;
    }

    int MP4BoxSTSC::SetDefaultData()
    {
        for(int i=0;i<3;i++){
            MP4BoxSTSCChunk * chunk = new MP4BoxSTSCChunk();
            chunk->first_chunk = i * 10;
            chunk->samples_per_chunk = i * 100;
            chunk->sample_description_index = i;
            chunkList.push_back(chunk);
        }

        size = Serialize().GetLen();

        return 0;
    }
}