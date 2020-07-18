#include "EyerPlayerLib.h"


namespace EyerPlayer {

    StreamInfo::StreamInfo()
    {

    }

    StreamInfo::~StreamInfo()
    {

    }

    StreamInfo::StreamInfo(StreamInfo & info)
    {
        *this = info;
    }

    StreamInfo & StreamInfo::operator = (StreamInfo & info)
    {
        type = info.type;
        width = info.width;
        height = info.height;
        duration = info.duration;
        timeBaseNum = info.timeBaseNum;
        timeBaseDen = info.timeBaseDen;

        return *this;
    }
}
