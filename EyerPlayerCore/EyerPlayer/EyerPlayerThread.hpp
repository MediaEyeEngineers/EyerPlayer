#ifndef EYERPLAYERLIB_THREAD_H
#define EYERPLAYERLIB_THREAD_H

#include "EyerOpenSL/EyerOpenSL.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerAV/EyerAVQueue.hpp"
#include "PlayerQueueManager.hpp"
#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerCodec/EyerCodec.hpp"
#include "EyerPlayerThread.hpp"
#include "MediaInfo.hpp"
#include "EyerPlayer.hpp"

namespace Eyer {
    class AVReaderThread;
    class AVDecoderThread;
    class PlayCtrThread;

    /**
     *
     * Reader
     *
     */
    enum AVReaderStatus
    {
        READER_STATUS_WAIT = 1,
        READER_STATUS_OPEN_SUCCESS = 2,
        READER_STATUS_OPEN_FAIL = 3,
    };
    class AVReaderThread : public Eyer::EyerThread
    {
    public:
        AVReaderThread(Eyer::EyerString _url, const Eyer::EyerPlayerConfig &_playerConfig, long long _openEventId, EyerEventQueue *_eventQueue, AVFrameQueueManager *_frameQueueManager);

        ~AVReaderThread();

        virtual void Run();

        int Seek(double time);

        int SetSurface(jobject _surface);

        const MediaInfo GetMediaInfo();

    private:
        Eyer::EyerString url;
        long long openEventId = -1;
        Eyer::EyerEventQueue * eventQueue = nullptr;
        AVFrameQueueManager * frameQueueManager = nullptr;

        jobject surface = nullptr;

        AVDecoderThread * audioThread = nullptr;
        AVDecoderThread * videoThread = nullptr;

        Eyer::EyerAVReader * reader = nullptr;

        Eyer::EyerPlayerConfig playerConfig;

        MediaInfo mediaInfo;
    };


    /**
     *
     * Decoder
     *
     */
    class AVDecoderThread : public Eyer::EyerThread
    {
    public:
        AVDecoderThread(Eyer::EyerAVStream & stream, AVFrameQueueManager * frameQueueManager);
        virtual ~AVDecoderThread();

        virtual void Run() = 0;

        int SendPacket(Eyer::EyerAVPacket * pkt);

        int GetPacketCount();
        int GetPacketSize();

        int ClearAllPacket();
        virtual int FlushDecoder() = 0;
    protected:
        Eyer::EyerAVQueue<Eyer::EyerAVPacket> pktQueue;

        std::atomic_int cacheSize {0};

        AVFrameQueueManager * frameQueueManager = nullptr;
        Eyer::EyerAVStream stream;
    };

    class AVDecoderThreadSoftware : public AVDecoderThread
    {
    public:
        AVDecoderThreadSoftware(Eyer::EyerAVStream & stream, AVFrameQueueManager * frameQueueManager);
        ~AVDecoderThreadSoftware();

        virtual void Run();

        virtual int FlushDecoder();

    private:
        Eyer::EyerAVDecoder decoder;
    };

    class AVDecoderThreadMediaCodec : public AVDecoderThread
    {
    public:
        AVDecoderThreadMediaCodec(Eyer::EyerAVStream & stream, AVFrameQueueManager * frameQueueManager, jobject surface);
        ~AVDecoderThreadMediaCodec();

        virtual void Run();

        virtual int FlushDecoder();

    private:
        jobject surface = nullptr;

        int inputIndex = -1;
    };


    /**
     *
     * Play Ctr
     *
     */
    enum AVPlayCtrStatus{
        STATUS_PLAYING = 1,
        STATUS_PAUSEING = 2
    };

    class AVPlayCtrThread : public Eyer::EyerThread
    {
    public:
        AVPlayCtrThread(const Eyer::EyerPlayerConfig & _playerConfig, AVFrameQueueManager * frameQueueManager, EyerEventQueue * eventQueue, MediaInfo & mediaInfo, double videoTime);
        ~AVPlayCtrThread();

        virtual void Run();

        int Play();
        int Pause();
        int Seek(double time);
    private:
        Eyer::EyerPlayerConfig playerConfig;
        AVFrameQueueManager * frameQueueManager = nullptr;
        EyerEventQueue * eventQueue = nullptr;

        std::mutex statusMut;
        AVPlayCtrStatus status = AVPlayCtrStatus::STATUS_PLAYING;

        EyerOpenSL * opensl = nullptr;

        MediaInfo mediaInfo;

        double seekTime = 0;
        long long startTime = 0;

        double pauseSeekTime = 0;

        double dTime = 0.0;


        int outindex = -1;
        long long videoFrameTime = 0;

        Eyer::EyerAVFrame * videoFrame = nullptr;
        Eyer::EyerAVFrame * audioFrame = nullptr;
    };
}

#endif // EYERPLAYERLIB_THREAD_H
