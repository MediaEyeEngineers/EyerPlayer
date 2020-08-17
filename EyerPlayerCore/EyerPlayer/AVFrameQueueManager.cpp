#include "PlayerQueueManager.hpp"

namespace EyerPlayer {
    AVFrameQueueManager::AVFrameQueueManager()
    {

    }

    AVFrameQueueManager::~AVFrameQueueManager()
    {

    }

    int AVFrameQueueManager::GetQueue(Eyer::EyerString key, AVFrameQueue * * queue)
    {
        return queueManager.GetQueue(key, queue);
    }

    int AVFrameQueueManager::ClearAndDelete()
    {
        return queueManager.ClearAndDelete();
    }

    int AVFrameQueueManager::GetMediaCodecQueue(Eyer::EyerMediaCodec * * mediaCodecQueue)
    {
        return 0;
    }
}