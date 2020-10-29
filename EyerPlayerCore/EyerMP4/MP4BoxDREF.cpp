#include "MP4BoxDREF.hpp"
#include "MP4Stream.hpp"
#include "MP4BoxURL.hpp"
#include "MP4BoxURN.hpp"

namespace Eyer
{
    MP4BoxDREF::MP4BoxDREF() : MP4FullBox()
    {
        type = BoxType::DREF;
    }

    MP4BoxDREF::~MP4BoxDREF()
    {

    }

    bool MP4BoxDREF::operator == (const MP4BoxDREF & dref) const
    {
        if(!MP4FullBox::operator==(dref)){
            return false;
        }
        return false;
    }

    EyerBuffer MP4BoxDREF::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        // return stream.GetBuffer();
        buffer.Append(drefBuffer);

        return buffer;
    }

    int MP4BoxDREF::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        drefBuffer = stream.GetBuffer();

        uint32_t entry_count = stream.ReadBigEndian_uint32(offset);

        for(int i=0;i<entry_count;i++){
            EyerBuffer buf = stream.GetBuffer();

            // TODO DREF
            MP4Box box;
            box.Parse(buf);
            if(box.GetType() == BoxType::URL){
                MP4BoxURL url;
                url.Parse(buf);
            }
            else if(box.GetType() == BoxType::URN){

            }
        }

        return offset;
    }

    int MP4BoxDREF::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";



        return 0;
    }

    int MP4BoxDREF::SetDefaultData()
    {
        return 0;
    }
}