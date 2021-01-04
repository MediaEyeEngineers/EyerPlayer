#ifndef EYERLIB_EYERDASHSTREAMREADERTHREAD_HPP
#define EYERLIB_EYERDASHSTREAMREADERTHREAD_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"
#include "EyerMPD.hpp"
#include "MP4Buffer.hpp"

namespace Eyer
{
    typedef EyerLockQueue<MP4Buffer> BufferQueue;

    class EyerDASHStreamReaderThread : public EyerThread {
    public:
        EyerDASHStreamReaderThread(EyerString & _mpdUrl, int _videoStreamIndex, int _audioStreamIndex, int _startFragmentIndex, BufferQueue * _mp4BufferQueue);
        ~EyerDASHStreamReaderThread();

        int SetEndIndex(int _endFragmentIndex);

        virtual void Run();

    private:
        EyerString mpdUrl;
        int videoStreamIndex = -1;
        int audioStreamIndex = -1;

        int startFragmentIndex = -1;
        int endFragmentIndex = -1;

        BufferQueue * mp4BufferQueue = nullptr;

        EyerBuffer ReadHeadBuffer(Eyer::EyerMPD & mpd);

        EyerBuffer MergeVideoAudio(MP4Box & videoBox, MP4Box & audioBox);
        EyerBuffer MergeAllTrack(Eyer::EyerMPD & mpd);
    };
}

#endif //EYERLIB_EYERDASHSTREAMREADERTHREAD_HPP
