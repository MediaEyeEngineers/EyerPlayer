#include "EyerPlayer.hpp"

#include "EyerPlayerPrivate.hpp"
#include "PlayerEvent.hpp"

namespace Eyer
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
        long long requestId = piml->eventManager->GenId();

        EventPlayRequest * event = new EventPlayRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(requestId);

        piml->eventManager->PushEvent(event);

        return 0;
    }

    int EyerPlayer::Pause()
    {
        long long requestId = piml->eventManager->GenId();

        EventPauseRequest * event = new EventPauseRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(requestId);

        piml->eventManager->PushEvent(event);
        return 0;
    }

    int EyerPlayer::Stop()
    {
        long long requestId = piml->eventManager->GenId();

        EventStopRequest * event = new EventStopRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(requestId);

        piml->eventManager->PushEvent(event);

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

    int EyerPlayer::SetSurface(jobject _surface)
    {
        return piml->eventManager->SetSurface(_surface);
    }

    int EyerPlayer::SetCallback(EyerPlayerCallback * callback)
    {
        return piml->eventManager->SetCallback(callback);
    }
}