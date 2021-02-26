#include "MediaInfo.hpp"

namespace Eyer {
    StreamInfo::StreamInfo()
    {

    }

    StreamInfo::StreamInfo(const StreamInfo & streamInfo)
    {
        *this = streamInfo;
    }

    StreamInfo::~StreamInfo()
    {

    }

    StreamInfo & StreamInfo::operator = (const StreamInfo & streamInfo)
    {
        width = streamInfo.width;
        height = streamInfo.height;

        audioSampleRate = streamInfo.audioSampleRate;
        audioChannels = streamInfo.audioChannels;
        videoOrAudioCodecName = streamInfo.videoOrAudioCodecName;

        return *this;
    }

    int StreamInfo::GetWidth()
    {
        return width;
    }

    int StreamInfo::GetHeight()
    {
        return height;
    }

    int StreamInfo::SetWH(int w, int h)
    {
        width = w;
        height = h;
        return 0;
    }


}