#include "EyerPlayer.hpp"

#include "EyerPlayerPrivate.hpp"

#include "EyerEvent/EyerEventHeader.hpp"

namespace Eyer
{
    EyerPlayer::EyerPlayer()
    {
        piml = new EyerPlayerPrivate();
        piml->threadEventLoop = new ThreadEventLoop();
        piml->threadEventLoop->Start();
    }

    EyerPlayer::~EyerPlayer()
    {
        if(piml->threadEventLoop != nullptr){
            piml->threadEventLoop->Stop();
            delete piml->threadEventLoop;
            piml->threadEventLoop = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerPlayer::Play()
    {
        std::lock_guard<std::mutex> lg(piml->mut);

        EyerSmartPtr<EventRequest_Play> event(new EventRequest_Play());
        piml->threadEventLoop->PushEvent(event);

        return 0;
    }

    int EyerPlayer::Pause()
    {
        std::lock_guard<std::mutex> lg(piml->mut);

        EyerSmartPtr<EventRequest> event(new EventRequest_Pause());
        piml->threadEventLoop->PushEvent(event);
        return 0;
    }

    int EyerPlayer::Resume()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        EyerSmartPtr<EventRequest> event(new EventRequest());
        piml->threadEventLoop->PushEvent(event);
        return 0;
    }

    int EyerPlayer::Stop()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        EyerSmartPtr<EventRequest> event(new EventRequest_Stop());
        piml->threadEventLoop->PushEvent(event);
        return 0;
    }
}