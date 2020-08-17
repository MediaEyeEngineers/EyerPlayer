#ifndef EYERPLAYERLIB_PLAYER_AV_FRAME_QUEUE_MANAGER_H
#define EYERPLAYERLIB_PLAYER_AV_FRAME_QUEUE_MANAGER_H

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerAV/EyerAVQueueManager.hpp"
#include "EyerAV/EyerAVQueue.hpp"

namespace EyerPlayer {
    typedef Eyer::EyerAVQueue<Eyer::EyerAVFrame> AVFrameQueue;
    // typedef Eyer::EyerAVQueueManager<AVFrameQueue> AVFrameQueueManager;

    class AVFrameQueueManager
    {
    public:
        AVFrameQueueManager();
        ~AVFrameQueueManager();

        int GetQueue(Eyer::EyerString key, AVFrameQueue * * queue);
        int ClearAndDelete();

        int GetMediaCodecQueue(Eyer::EyerMediaCodec * * mediaCodecQueue);

    private:
        Eyer::EyerAVQueueManager<AVFrameQueue> queueManager;
    };
}

#endif // EYERPLAYERLIB_PLAYER_AV_FRAME_QUEUE_MANAGER_H