#include "MP4BoxURN.hpp"

namespace Eyer
{
    MP4BoxURN::MP4BoxURN() : MP4FullBox()
    {

    }

    MP4BoxURN::~MP4BoxURN()
    {

    }

    bool MP4BoxURN::operator == (const MP4BoxURN & urn) const
    {
        return true;
    }

    EyerBuffer MP4BoxURN::SerializeParam()
    {
        EyerBuffer buffer;
        return buffer;
    }

    int MP4BoxURN::ParseParam(EyerBuffer & buffer, int offset)
    {
        return 0;
    }

    int MP4BoxURN::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        // printf("%slocation: %s\n", levelStr.str, location.str);

        return 0;
    }

    int MP4BoxURN::SetDefaultData()
    {
        return 0;
    }
}