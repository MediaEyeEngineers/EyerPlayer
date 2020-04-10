#include "EyerPlayerLib.h"


namespace EyerPlayer {

    MediaInfo::MediaInfo()
    {

    }

    MediaInfo::~MediaInfo()
    {
        for(int i=0; i<streamList.size(); i++){
            StreamInfo * streamInfo = streamList[i];
            if(streamInfo != nullptr){
                delete streamInfo;
            }
        }
        streamList.clear();
    }

    MediaInfo::MediaInfo(MediaInfo & mediaInfo)
    {
        *this = mediaInfo;
    }

    MediaInfo & MediaInfo::operator = (MediaInfo & mediaInfo)
    {
        if(this == &mediaInfo){
            return *this;
        }

        duration = mediaInfo.duration;

        for(int i=0; i<mediaInfo.streamList.size(); i++){
            StreamInfo * info = mediaInfo.streamList[i];
            if(info != nullptr){
                StreamInfo * streamInfo = new StreamInfo(*info);
                streamList.push_back(streamInfo);
            }
        }
        return *this;
    }

    int MediaInfo::AddStreamInfo(StreamInfo & _streamInfo)
    {
        StreamInfo * streamInfo = new StreamInfo(_streamInfo);
        streamList.push_back(streamInfo);
        return 0;
    }

    int MediaInfo::GetStreamCount()
    {
        return streamList.size();
    }

    int MediaInfo::GetStream(int index, StreamInfo & streamInfo)
    {
        StreamInfo * streamInfoIner = streamList.at(index);
        streamInfo = * streamInfoIner;

        return 0;
    }
}
