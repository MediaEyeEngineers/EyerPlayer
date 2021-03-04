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
        EyerLog("==========================*MediaInfo*==========================\n");
        EyerLog("Video Stream\n");
        EyerLog("Video Codec: %s\n", videoStream.videoOrAudioCodecName.data());
        EyerLog("Width: %d, Height: %d\n", videoStream.GetWidth(), videoStream.GetHeight());
        EyerLog("Audio Stream\n");
        EyerLog("Audio Codec: %s\n", audioStream.videoOrAudioCodecName.data());
        EyerLog("Audio SampleRate: %d, Channels: %d\n",audioStream.audioSampleRate, audioStream.audioChannels);
        EyerLog("=========================**MediaInfo**==========================\n");
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

    int MediaInfo::setAudioInformation(int _audioSampleRate,int _audioChannels){
        audioStream.audioSampleRate = _audioSampleRate;
        audioStream.audioChannels = _audioChannels;
        return 0;
    }

    int MediaInfo::setVideoAndAudioInformation(std::string videoCodecName,std::string audioCodecName){
        videoStream.videoOrAudioCodecName = videoCodecName;

        audioStream.videoOrAudioCodecName = audioCodecName;

        return 0;
    }
}