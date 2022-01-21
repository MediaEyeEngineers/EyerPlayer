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

    int EyerPlayer::SetURL(const EyerString & _url)
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        piml->url = _url;
        return 0;
    }

    int EyerPlayer::Play()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        EventRequest_Play * event = new EventRequest_Play();
        event->url = piml->url;
        piml->threadEventLoop->PushEvent(event);
        return 0;
    }

    int EyerPlayer::Pause()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        EventRequest_Pause * event = new EventRequest_Pause();
        piml->threadEventLoop->PushEvent(event);
        return 0;
    }

    int EyerPlayer::Resume()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        EventRequest_Resume * event = new EventRequest_Resume();
        piml->threadEventLoop->PushEvent(event);
        return 0;
    }

    int EyerPlayer::Stop()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        EventRequest_Stop * event = new EventRequest_Stop();
        piml->threadEventLoop->PushEvent(event);
        return 0;
    }

    int EyerPlayer::Seek(double time)
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        EventRequest_Seek * event = new EventRequest_Seek();
        piml->threadEventLoop->PushEvent(event);
        return 0;
    }
}