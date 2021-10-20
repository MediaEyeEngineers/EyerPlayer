#ifndef EYERPLAYER_EYERDEOCDEQUEUE_HPP
#define EYERPLAYER_EYERDEOCDEQUEUE_HPP

#include "EyerAV/EyerAV.hpp"

namespace Eyer
{
    class EyerDeocdeQueue
    {
    public:
        EyerDeocdeQueue(const EyerAVStream & stream);
        virtual ~EyerDeocdeQueue();

        virtual int Start() = 0;
        virtual int Stop() = 0;
        virtual int PutPacket(EyerAVPacket & packet) = 0;

    protected:
        EyerAVStream stream;
    };
}



#endif //EYERPLAYER_EYERDEOCDEQUEUE_HPP
