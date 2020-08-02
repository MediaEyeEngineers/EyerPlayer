#ifndef EYERPLAYERLIB_PLAYER_MEDIAINFO_H
#define EYERPLAYERLIB_PLAYER_MEDIAINFO_H

namespace EyerPlayer {

    enum StreamType
    {
        STREAM_TYPE_UNKNOW = -1,
        STREAM_TYPE_VIDEO = 0,
        STREAM_TYPE_AUDIO = 1
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
        StreamType type = StreamType::STREAM_TYPE_UNKNOW;
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