#ifndef EYERPLAYERLIB_THREAD_H
#define EYERPLAYERLIB_THREAD_H

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerAV/EyerAVQueue.hpp"
#include "PlayerQueueManager.hpp"
#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerCodec/EyerCodec.hpp"

namespace Eyer {
    class AVReaderThread;
    class AVDecoderThread;
    class PlayCtrThread;

    /**
     *
     * Reader
     *
     */
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


    /**
     *
     * Decoder
     *
     */
    class AVDecoderThread : public Eyer::EyerThread
    {
    public:
        AVDecoderThread(Eyer::EyerAVStream & stream, AVFrameQueueManager * frameQueueManager);
        ~AVDecoderThread();

        virtual void Run() = 0;

        int SendPacket(Eyer::EyerAVPacket * pkt);

        int GetPacketCount();
        int GetPacketSize();

    protected:
        Eyer::EyerAVQueue<Eyer::EyerAVPacket> pktQueue;

        int cacheSize = 0;

        AVFrameQueueManager * frameQueueManager = nullptr;
        Eyer::EyerAVStream stream;
    };

    class AVDecoderThreadSoftware : public AVDecoderThread
    {
    public:
        AVDecoderThreadSoftware(Eyer::EyerAVStream & stream, AVFrameQueueManager * frameQueueManager);
        ~AVDecoderThreadSoftware();

        virtual void Run();

    private:
        Eyer::EyerAVDecoder decoder;
    };

    class AVDecoderThreadMediaCodec : public AVDecoderThread
    {
    public:
        AVDecoderThreadMediaCodec(Eyer::EyerAVStream & stream, AVFrameQueueManager * frameQueueManager);
        ~AVDecoderThreadMediaCodec();

        virtual void Run();

    private:
    };


    /**
     *
     * Play Ctr
     *
     */
    class AVPlayCtrThread : public Eyer::EyerThread
    {
    public:
        AVPlayCtrThread(AVFrameQueueManager * frameQueueManager);
        ~AVPlayCtrThread();

        virtual void Run();

        int SetGLCtx(Eyer::EyerGLContextThread * glCtx);

    private:
        AVFrameQueueManager * frameQueueManager = nullptr;

        std::mutex mut;
        Eyer::EyerGLContextThread * glCtx = nullptr;
    };
}

#endif // EYERPLAYERLIB_THREAD_H
