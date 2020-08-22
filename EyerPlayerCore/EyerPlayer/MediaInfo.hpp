#ifndef EYERPLAYER_LIB_PLAYER_MEDIA_STREAM_INFO_H
#define EYERPLAYER_LIB_PLAYER_MEDIA_STREAM_INFO_H

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

    public:
        StreamInfo audioStream;
        StreamInfo videoStream;
    };
}

#endif // EYERPLAYERLIB_PLAYER_MEDIAINFO_H