#include "MediaInfo.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer {
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
        duration = mediaInfo.duration;
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

    double MediaInfo::GetDuration()
    {
        return duration;
    }

    int MediaInfo::SetDuration(double _duration)
    {
        duration = _duration;
        return 0;
    }
}