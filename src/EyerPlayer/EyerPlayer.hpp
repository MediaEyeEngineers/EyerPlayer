#ifndef EYERCAMERA_EYERPLAYER_HPP
#define EYERCAMERA_EYERPLAYER_HPP

#include "QueueBox.hpp"

namespace Eyer
{
    class EyerPlayerPrivate;

    class EyerPlayer
    {
    public:
        EyerPlayer();
        ~EyerPlayer();

        int Play();
        int Pause();
        int Resume();
        int Stop();

        // Output
        QueueBox * GetQueueBox();
    private:
        EyerPlayerPrivate * piml = nullptr;
    };
}



#endif //EYERCAMERA_EYERPLAYER_HPP
