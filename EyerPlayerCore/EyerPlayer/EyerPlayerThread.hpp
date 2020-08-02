#ifndef EYERPLAYERLIB_THREAD_H
#define EYERPLAYERLIB_THREAD_H

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerAV/EyerAVQueue.hpp"
#include "PlayerQueueManager.hpp"
#include "EyerGLContext/EyerGLContext.hpp"

namespace EyerPlayer {
    class AVReaderThread;
    class AVDecoderThread;
    class PlayCtrThread;

    class AVReaderThread : public Eyer::EyerThread
    {
    public:
        AVReaderThread(Eyer::EyerString url, long long openEventId, Eyer::EyerEventQueue * eventQueue, AVFrameQueueManager * frameQueueManager);
        ~AVReaderThread();
        virtual void Run();

        int SetGLCtx(Eyer::EyerGLContextThread * glCtx);

    private:
        Eyer::EyerString url;
        long long openEventId = -1;
        Eyer::EyerEventQueue * eventQueue = nullptr;

        AVDecoderThread * audioThread = nullptr;
        AVDecoderThread * videoThread = nullptr;

        AVFrameQueueManager * frameQueueManager = nullptr;

        Eyer::EyerGLContextThread * glCtx = nullptr;
    };

    class AVDecoderThread : public Eyer::EyerThread
    {
    public:
        AVDecoderThread(Eyer::EyerAVStream * stream, Eyer::EyerAVRational timebase, Eyer::EyerAVStreamType streamType, AVFrameQueueManager * frameQueueManager);
        ~AVDecoderThread();

        virtual void Run();

        int SendPacket(Eyer::EyerAVPacket * pkt);

        int GetPacketCount();
        int GetPacketSize();

    private:
        Eyer::EyerAVDecoder decoder;
        Eyer::EyerAVQueue<Eyer::EyerAVPacket> pktQueue;

        int cacheSize = 0;

        AVFrameQueueManager * frameQueueManager = nullptr;

        Eyer::EyerAVStreamType streamType = Eyer::EyerAVStreamType::STREAM_TYPE_UNKNOW;

        Eyer::EyerAVRational timebase;
    };

    class PlayCtrThread : public Eyer::EyerThread
    {
    public:
        PlayCtrThread(AVFrameQueueManager * frameQueueManager);
        ~PlayCtrThread();

        virtual void Run();

        int SetGLCtx(Eyer::EyerGLContextThread * glCtx);

    private:
        AVFrameQueueManager * frameQueueManager = nullptr;
        Eyer::EyerGLContextThread * glCtx = nullptr;
    };
}

#endif // EYERPLAYERLIB_THREAD_H
