#ifndef	EYER_PLAYER_EVENT_MANAGER_H
#define	EYER_PLAYER_EVENT_MANAGER_H

#include "EyerThread/EyerThread.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerPlayerThread.hpp"
#include "EyerPlayerThreadManager.hpp"

namespace EyerPlayer 
{
    class EyerPlayerEventManager : public Eyer::EyerThread 
    {
    public:
        EyerPlayerEventManager();
        ~EyerPlayerEventManager();

        virtual void Run();

        int PushEvent(Eyer::EyerEvent * event);
        long long GenId();

    private:
        Eyer::EyerEventQueue * eventQueue = nullptr;
        EyerPlayerThreadManager * playerManager = nullptr;
    };
}

#endif