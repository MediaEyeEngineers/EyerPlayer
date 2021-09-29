#include "EyerPlayer.hpp"

#include "EyerPlayerPrivate.hpp"

namespace Eyer
{
    EyerPlayer::EyerPlayer()
    {
        piml = new EyerPlayerPrivate();
    }

    EyerPlayer::~EyerPlayer()
    {
        Stop();
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerPlayer::Start()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        if(piml->threadReader == nullptr){
            piml->threadReader = new ThreadReader();
            piml->threadReader->Start();
        }
        else {
            return -1;
        }

        return 0;
    }

    int EyerPlayer::Pause()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        return 0;
    }

    int EyerPlayer::Stop()
    {
        std::lock_guard<std::mutex> lg(piml->mut);
        if(piml->threadReader != nullptr){
            piml->threadReader->Stop();
            delete piml->threadReader;
            piml->threadReader = nullptr;
        }
        return 0;
    }
}