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
        audioStream     = mediaInfo.audioStream;
        videoStream     = mediaInfo.videoStream;
        duration        = mediaInfo.duration;

        return *this;
    }

    int MediaInfo::Print()
    {
        EyerLog("==========================*MediaInfo*==========================\n");
        EyerLog("Video Stream\n");
        EyerLog("Width: %d, Height: %d\n", videoStream.width, videoStream.height);
        EyerLog("Audio Stream\n");
        EyerLog("Audio SampleRate: %d, Channels: %d\n",audioStream.audioSampleRate, audioStream.audioChannels);
        EyerLog("=========================**MediaInfo**==========================\n");

        return 0;
    }
}