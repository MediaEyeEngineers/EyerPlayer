#ifndef EYERCAMERA_EYERPLAYER_HPP
#define EYERCAMERA_EYERPLAYER_HPP

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

    private:
        EyerPlayerPrivate * piml = nullptr;
    };
}



#endif //EYERCAMERA_EYERPLAYER_HPP
