#include "MediaInfo.hpp"
#include "EyerCore/EyerCore.hpp"

namespace EyerPlayer {
    MediaInfo::MediaInfo()
    {
        
    }

    MediaInfo::MediaInfo(const MediaInfo & mediaInfo)
    {
        *this = mediaInfo;
    }

    MediaInfo::~MediaInfo()
    {

    }

    MediaInfo & MediaInfo::operator = (const MediaInfo & mediaInfo)
    {
        audioStream = mediaInfo.audioStream;
        videoStream = mediaInfo.videoStream;
        return *this;
    }

    int MediaInfo::Print()
    {
        EyerLog("==========================MediaInfo==========================\n");
        EyerLog("Video Stream\n");
        EyerLog("Width: %d, Height: %d\n", videoStream.GetWidth(), videoStream.GetHeight());
        EyerLog("Audio Stream\n");
        EyerLog("==========================MediaInfo==========================\n");
        return 0;
    }
}