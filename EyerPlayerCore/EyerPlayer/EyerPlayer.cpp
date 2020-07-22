#include "EyerPlayer.hpp"

#include "EyerPlayerPrivate.hpp"

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

    int EyerPlayer::SetURL(std::string url)
    {
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

    int EyerPlayer::BindGLContext(EyerGLContextThread * ctx)
    {
        return 0;
    }

    int EyerPlayer::UnBindGLContext()
    {
        return 0;
    }
}