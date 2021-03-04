#ifndef EYERPLAYER_LIB_PLAYER_MEDIA_STREAM_INFO_H
#define EYERPLAYER_LIB_PLAYER_MEDIA_STREAM_INFO_H

#include <string>
namespace Eyer {
    enum StreamType
    {
        PLAYER_STREAM_TYPE_UNKNOW = -1,
        PLAYER_STREAM_TYPE_VIDEO = 0,
        PLAYER_STREAM_TYPE_AUDIO = 1
    };




    class MediaInfo;
    class StreamInfo;

    class StreamInfo {
    public:
        StreamInfo();
        StreamInfo(const StreamInfo & streamInfo);
        ~StreamInfo();

        StreamInfo & operator = (const StreamInfo & streamInfo);

        int GetWidth();
        int GetHeight();

        int SetWH(int w, int h);

    public:

        // 音视频编解码器
        std::string videoOrAudioCodecName;

        // 音频的采样率;
        int audioSampleRate = 0;
        // 音频的通道数
        int audioChannels = 0;



    private:
        StreamType type = StreamType::PLAYER_STREAM_TYPE_UNKNOW;
        int width = 0;
        int height = 0;
    };


    class MediaInfo {
    public:
        MediaInfo();
        MediaInfo(const MediaInfo & mediaInfo);
        ~MediaInfo();

        MediaInfo & operator = (const MediaInfo & mediaInfo);

        int Print();

        double GetDuration();
        int SetDuration(double duration);

        int setAudioInformation(int audioSampleRate,int audioChannels);

        int setVideoAndAudioInformation(std::string videoCodecName,std::string audioCodecName);


    public:
        StreamInfo audioStream;
        StreamInfo videoStream;




    private:
        double duration = 0.0;
    };
}

#endif // EYERPLAYERLIB_PLAYER_MEDIAINFO_H