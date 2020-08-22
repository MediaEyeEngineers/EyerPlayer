#ifndef	EYER_PLAYER_EVENT_MANAGER_H
#define	EYER_PLAYER_EVENT_MANAGER_H

#include "EyerThread/EyerThread.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerPlayerThread.hpp"
#include "EyerPlayerThreadManager.hpp"
#include "EyerPlayer.hpp"

namespace Eyer
{
    class EyerPlayerEventManager : public Eyer::EyerThread 
    {
    public:
        EyerPlayerEventManager();
        ~EyerPlayerEventManager();

        virtual void Run();

        int PushEvent(Eyer::EyerEvent * event);
        long long GenId();

        int SetGLCtx(Eyer::EyerGLContextThread * _glCtx);
        int UnbindGLCtx();

        int SetSurface(jobject _surface);
        int SetCallback(EyerPlayerCallback * callback);

    private:
        Eyer::EyerEventQueue * eventQueue = nullptr;
        EyerPlayerThreadManager * playerManager = nullptr;
        EyerPlayerCallback * callback = nullptr;
    };
}

#endif