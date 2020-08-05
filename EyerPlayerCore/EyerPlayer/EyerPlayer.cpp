#include "EyerPlayer.hpp"

#include "EyerPlayerPrivate.hpp"
#include "PlayerEvent.hpp"

namespace EyerPlayer 
{
    EyerPlayer::EyerPlayer()
    {
        piml = new EyerPlayerPrivate();

        piml->eventManager = new EyerPlayerEventManager();
        piml->eventManager->Start();
    }

    EyerPlayer::~EyerPlayer()
    {
        if(piml->eventManager != nullptr){
            piml->eventManager->Stop();
            delete piml->eventManager;
            piml->eventManager = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerPlayer::Open(std::string url)
    {
        piml->url = url;

        long long requestId = piml->eventManager->GenId();

        EventOpenRequest * event = new EventOpenRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->url = url.c_str();
        event->SetRequestId(requestId);

        piml->eventManager->PushEvent(event);

        return 0;
    }

    int EyerPlayer::Play()
    {
        return 0;
    }

    int EyerPlayer::Pause()
    {
        return 0;
    }

    int EyerPlayer::Stop()
    {
        return 0;
    }

    int EyerPlayer::BindGLContext(Eyer::EyerGLContextThread * ctx)
    {
        return piml->eventManager->SetGLCtx(ctx);
    }

    int EyerPlayer::UnBindGLContext()
    {
        return piml->eventManager->UnbindGLCtx();
    }
}