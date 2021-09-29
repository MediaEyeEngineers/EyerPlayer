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

        int Start();
        int Pause();
        int Stop();

    private:
        EyerPlayerPrivate * piml = nullptr;
    };
}



#endif //EYERCAMERA_EYERPLAYER_HPP
