#ifndef EYERPLAYERLIB_PLAYER_AV_FRAME_QUEUE_MANAGER_H
#define EYERPLAYERLIB_PLAYER_AV_FRAME_QUEUE_MANAGER_H

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerAV/EyerAVQueueManager.hpp"
#include "EyerAV/EyerAVQueue.hpp"

namespace EyerPlayer {
typedef Eyer::EyerAVQueue<Eyer::EyerAVFrame> AVFrameQueue;
typedef Eyer::EyerAVQueueManager<AVFrameQueue> AVFrameQueueManager;
}

#endif // EYERPLAYERLIB_PLAYER_AV_FRAME_QUEUE_MANAGER_H