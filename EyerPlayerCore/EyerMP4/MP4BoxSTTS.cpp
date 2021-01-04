#include "MP4BoxSTTS.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxSTTS::MP4BoxSTTS() : MP4FullBox()
    {
        type = BoxType::STTS;
    }

    MP4BoxSTTS::~MP4BoxSTTS()
    {
        for(int i=0;i<sampleList.size();i++){
            delete sampleList[i];
        }
        sampleList.clear();
    }

    bool MP4BoxSTTS::operator == (const MP4BoxSTTS & stts) const
    {
        if(!MP4FullBox::operator==(stts)){
            return false;
        }
        if(sampleList.size() != stts.sampleList.size()){
            return false;
        }
        for(int i=0;i<sampleList.size();i++) {
            if(sampleList[i]->sample_count != stts.sampleList[i]->sample_count){
                return false;
            }
            if(sampleList[i]->sample_delta != stts.sampleList[i]->sample_delta){
                return false;
            }
        }

        return true;
    }

    EyerBuffer MP4BoxSTTS::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        stream.WriteBigEndian((uint32_t)sampleList.size());

        for(int i=0;i<sampleList.size();i++){
            stream.WriteBigEndian(sampleList[i]->sample_count);
            stream.WriteBigEndian(sampleList[i]->sample_delta);
        }

        return stream.GetBuffer();
    }

    int MP4BoxSTTS::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        uint32_t entry_count = stream.ReadBigEndian_uint32(offset);
        for(int i=0;i<entry_count;i++){
            MP4BoxSTTSSample * sample = new MP4BoxSTTSSample();
            sample->sample_count = stream.ReadBigEndian_uint32(offset);
            sample->sample_delta = stream.ReadBigEndian_uint32(offset);
            sampleList.push_back(sample);
        }

        return offset;
    }

    int MP4BoxSTTS::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        for(int i=0;i<sampleList.size();i++){
            printf("%ssample_count: %d\n", levelStr.str, sampleList[i]->sample_count);
            printf("%ssample_delta: %d\n", levelStr.str, sampleList[i]->sample_delta);
        }

        return 0;
    }

    int MP4BoxSTTS::SetDefaultData()
    {
        for(int i=0;i<3;i++){
            MP4BoxSTTSSample * sample = new MP4BoxSTTSSample();
            sample->sample_count = i;
            sample->sample_delta = i * 10;
            sampleList.push_back(sample);
        }

        size = Serialize().GetLen();

        return 0;
    }
}