#ifndef EYER_LIB_EYERDASHSTREAM_HPP
#define EYER_LIB_EYERDASHSTREAM_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerDASHStreamReaderThread.hpp"
#include "MP4Buffer.hpp"

namespace Eyer
{
    typedef EyerLockQueue<MP4Buffer> BufferQueue;

    class EyerDASHStream {
    public:
        EyerDASHStream(const EyerString & _mpdUrl, int _videoStreamIndex, int _audioStreamIndex, int _startFragmentIndex);
        ~EyerDASHStream();

        int StartLoad();
        int StopLoad();

        int SetEndIndex(int _endFragmentIndex);

        int GetStartIndex();
        int GetEndIndex();

        int PopMP4Buffer(MP4Buffer * * buffer);
        int GetMP4BuffeQueueSize();

    private:
        EyerString mpdUrl;
        int videoStreamIndex = -1;
        int audioStreamIndex = -1;
        int startFragmentIndex = -1;
        int endFragmentIndex = -1;

        BufferQueue mp4BufferQueue;

        EyerDASHStreamReaderThread * streamReaderThread = nullptr;
    };
}

#endif //EYER_LIB_EYERDASHSTREAM_HPP
