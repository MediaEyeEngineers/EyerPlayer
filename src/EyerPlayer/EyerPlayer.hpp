#ifndef EYERPLAYER_EYERPLAYER_HPP
#define EYERPLAYER_EYERPLAYER_HPP

#include "EyerCore/EyerCore.hpp"

#include "EventControlThread.hpp"

namespace Eyer
{
    class EyerPlayer
    {
    public:
        EyerPlayer();
        ~EyerPlayer();

        int SetURL(const EyerString & _url);
        int Play();
        int Stop();

    private:
        EyerString url;
        EventControlThread * eventControlThread = nullptr;
    };
}

#endif //EYERPLAYER_EYERPLAYER_HPP
