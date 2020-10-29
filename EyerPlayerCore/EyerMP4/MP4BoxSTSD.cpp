#include "MP4BoxSTSD.hpp"
#include "MP4Stream.hpp"

#include "MP4BoxAVC1.hpp"
#include "MP4BoxSampleEntry.hpp"

namespace Eyer
{
    MP4BoxSTSD::MP4BoxSTSD() : MP4FullBox()
    {
        type = BoxType::STSD;
    }

    MP4BoxSTSD::~MP4BoxSTSD()
    {
        for(int i=0;i<sampleList.size();i++){
            delete sampleList[i];
        }
        sampleList.clear();
    }

    bool MP4BoxSTSD::operator == (const MP4BoxSTSD & stsd) const
    {
        if(!MP4FullBox::operator==(stsd)){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxSTSD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        /*
        MP4Stream stream(buffer);
        return stream.GetBuffer();
        */
        buffer.Append(stsdBuffer);
        return buffer;
    }

    int MP4BoxSTSD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        // TODO Cache STSD
        stsdBuffer = stream.GetBuffer();

        uint32_t entry_count = stream.ReadBigEndian_uint32(offset);
        for(int i=0;i<entry_count;i++){
            int size = 0;
            BoxType type;
            stream.GetSizeType(size, type);

            EyerBuffer buf;
            stream.CutOff(buf, size);

            if(type == BoxType::AVC1){
                MP4BoxSampleEntry * avc1 = new MP4BoxAVC1();
                avc1->Parse(buf);

                sampleList.push_back(avc1);
            }

            offset += size;
        }

        return offset;
    }

    int MP4BoxSTSD::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        for(int i=0;i<sampleList.size();i++){
            sampleList[i]->PrintInfo(level + 1);
        }

        return 0;
    }

    int MP4BoxSTSD::SetDefaultData()
    {
        return 0;
    }
}