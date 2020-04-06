#ifndef EYERPLAYERVIEWPRIVATE_H
#define EYERPLAYERVIEWPRIVATE_H

#include "EyerPlayerEventManager.h"
#include "EyerPlayerVideoRender.h"
#include <map>

#include "PlayerTypedef.hpp"

namespace EyerPlayer {
    class EyerPlayerViewPrivate
    {
    public:
        EyerPlayerEventManager * eventManager = nullptr;
        std::map<long long, EyerPlayerOpenCB *> * openCBmap = nullptr;
        std::map<long long, EyerPlayerStopCB *> * stopCBmap = nullptr;

        AVFrameQueueManager * frameQueueManager = nullptr;

        AudioPlayThread * audioPlayThread = nullptr;
        EyerPlayerVideoRender * videoRender = nullptr;



    };
}

#endif // EYERPLAYERVIEWPRIVATE_H
