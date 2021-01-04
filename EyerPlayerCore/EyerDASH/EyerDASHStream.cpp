#include "EyerDASHStream.hpp"

namespace Eyer
{
    EyerDASHStream::EyerDASHStream(const EyerString & _mpdUrl, int _videoStreamIndex, int _audioStreamIndex, int _startFragmentIndex)
    {
        mpdUrl = _mpdUrl;
        videoStreamIndex = _videoStreamIndex;
        audioStreamIndex = _audioStreamIndex;
        startFragmentIndex = _startFragmentIndex;
        endFragmentIndex = -1;
    }

    EyerDASHStream::~EyerDASHStream()
    {
        StopLoad();
        while(mp4BufferQueue.Size()){
            MP4Buffer * buffer = nullptr;
            mp4BufferQueue.FrontPop(&buffer);
            if(buffer != nullptr){
                delete buffer;
                buffer = nullptr;
            }
        }
    }

    int EyerDASHStream::GetStartIndex()
    {
        return startFragmentIndex;
    }

    int EyerDASHStream::GetEndIndex()
    {
        return endFragmentIndex;
    }

    int EyerDASHStream::PopMP4Buffer(MP4Buffer * * buffer)
    {
        return mp4BufferQueue.FrontPop(buffer);
    }

    int EyerDASHStream::GetMP4BuffeQueueSize()
    {
        return mp4BufferQueue.Size();
    }

    int EyerDASHStream::SetEndIndex(int _endFragmentIndex)
    {
        endFragmentIndex = _endFragmentIndex;
        if(streamReaderThread != nullptr){
            streamReaderThread->SetEndIndex(endFragmentIndex);
        }
        return 0;
    }

    int EyerDASHStream::StartLoad()
    {
        StopLoad();
        streamReaderThread = new EyerDASHStreamReaderThread(mpdUrl, videoStreamIndex, audioStreamIndex, startFragmentIndex, &mp4BufferQueue);
        streamReaderThread->Start();
        return 0;
    }

    int EyerDASHStream::StopLoad()
    {
        if(streamReaderThread != nullptr){
            streamReaderThread->Stop();
            delete streamReaderThread;
            streamReaderThread = nullptr;
        }
        return 0;
    }
}
