#ifndef EYERCAMERA_THREADREADER_HPP
#define EYERCAMERA_THREADREADER_HPP

#include "EyerThread/EyerThread.hpp"
#include "QueueBox.hpp"
#include "ThreadPlayCtr.hpp"
#include "DecoderBox.hpp"
#include "EyerPlayerContext.hpp"

namespace Eyer
{
    class EventControlThread;

    class ThreadReader : public EyerThread
    {
    public:
        ThreadReader(EyerPlayerContext * _playerContext);
        ~ThreadReader();

        virtual void Run() override;

        virtual int SetStopFlag() override;
        virtual int SetStartEventLoopFlag() override;

    private:
        EyerAVReader * reader = nullptr;
        EyerPlayerContext * playerContext = nullptr;
    };
}

#endif //EYERCAMERA_THREADREADER_HPP
