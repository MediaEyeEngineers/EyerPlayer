#include "MP4BoxURL.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxURL::MP4BoxURL() : MP4FullBox()
    {
        type = BoxType::URL;
    }

    MP4BoxURL::~MP4BoxURL()
    {

    }

    bool MP4BoxURL::operator == (const MP4BoxURL & url) const
    {
        if(!MP4FullBox::operator==(url)){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxURL::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        return stream.GetBuffer();
    }

    int MP4BoxURL::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        stream.ReadStr(location, stream.GetBuffer().GetLen());

        return offset;
    }

    int MP4BoxURL::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%slocation: %s\n", levelStr.str, location.str);

        return 0;
    }

    int MP4BoxURL::SetDefaultData()
    {
        return 0;
    }
}