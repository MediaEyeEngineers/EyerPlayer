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

        return *this;
    }
}