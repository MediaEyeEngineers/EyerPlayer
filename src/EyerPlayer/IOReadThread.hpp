#ifndef EYERPLAYER_IOREADTHREAD_HPP
#define EYERPLAYER_IOREADTHREAD_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

#include "EyerPlayerContext.hpp"

namespace Eyer
{
    class IOReadThread : public EyerThread
    {
    public:
        IOReadThread(EyerPlayerContext * _playerContext);
        ~IOReadThread();

        virtual void Run() override;

        EyerPlayerContext * playerContext = nullptr;
        EyerAVReader * reader = nullptr;
    };
}

#endif //EYERPLAYER_IOREADTHREAD_HPP
