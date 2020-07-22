#ifndef	EYER_PLAYER_EVENT_MANAGER_H
#define	EYER_PLAYER_EVENT_MANAGER_H

#include "EyerThread/EyerThread.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"

namespace Eyer 
{
    class EyerPlayerEventManager : public EyerThread 
    {
    public:
        EyerPlayerEventManager();
        ~EyerPlayerEventManager();

        virtual void Run();

    private:
        EyerEventQueue * eventQueue = nullptr;
    };
}

#endif