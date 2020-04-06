#ifndef EYERPLAYERLIB_PLAYER_TYPEDEF_H
#define EYERPLAYERLIB_PLAYER_TYPEDEF_H

#include "EyerAV/EyerAVQueueManager.hpp"
#include "EyerAV/EyerAVQueue.hpp"
#include "EyerAV/EyerAV.hpp"

namespace EyerPlayer {
typedef Eyer::EyerAVQueue<Eyer::EyerAVFrame> AVFrameQueue;
typedef Eyer::EyerAVQueueManager<AVFrameQueue> AVFrameQueueManager;
}

#endif // EYERPLAYERLIB_PLAYER_TYPEDEF_H
