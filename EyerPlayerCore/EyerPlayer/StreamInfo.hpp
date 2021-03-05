#ifndef EYERPLAYER_LIB_PLAYER_STREAM_INFO_H
#define EYERPLAYER_LIB_PLAYER_STREAM_INFO_H

namespace Eyer
{
    enum StreamType
    {
        PLAYER_STREAM_TYPE_UNKNOW = -1,
        PLAYER_STREAM_TYPE_VIDEO = 0,
        PLAYER_STREAM_TYPE_AUDIO = 1
    };

    class StreamInfo {
    public:
        StreamInfo();
        StreamInfo(const StreamInfo & streamInfo);
        ~StreamInfo();

        StreamInfo & operator = (const StreamInfo & streamInfo);

    public:
        StreamType type = StreamType::PLAYER_STREAM_TYPE_UNKNOW;
        int width = 0;
        int height = 0;

        // 音频的采样率;
        int audioSampleRate = 0;
        // 音频的通道数
        int audioChannels = 0;
    };
}

#endif // EYERPLAYER_LIB_PLAYER_STREAM_INFO_H