#ifndef EYERCAMERA_THREADREADER_HPP
#define EYERCAMERA_THREADREADER_HPP

#include "EyerThread/EyerThread.hpp"
#include "QueueBox.hpp"
#include "ThreadPlayCtr.hpp"
#include "DecoderBox.hpp"

namespace Eyer
{
    class ThreadEventLoop;

    class ThreadReader : public EyerThread
    {
    public:
        ThreadReader(const EyerString & url, ThreadEventLoop * _eventLoop);
        ~ThreadReader();

        void _Run();
        virtual void Run() override;

        virtual int SetStopFlag() override;
        virtual int SetStartEventLoopFlag() override;

    private:
        ThreadEventLoop * eventLoop = nullptr;
        EyerString url = "";

        DecoderBox * decoderBox = nullptr;
        EyerAVReader * reader = nullptr;

        ThreadPlayCtr * playCtr = nullptr;
    };
}

#endif //EYERCAMERA_THREADREADER_HPP
