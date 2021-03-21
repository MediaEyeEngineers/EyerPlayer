#ifndef EYERPLAYER_LIB_PLAYER_MEDIA_STREAM_INFO_H
#define EYERPLAYER_LIB_PLAYER_MEDIA_STREAM_INFO_H

#include <string>
#include "StreamInfo.hpp"

namespace Eyer
{
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
        double duration = 0.0;
    };
}

#endif // EYERPLAYERLIB_PLAYER_MEDIAINFO_H