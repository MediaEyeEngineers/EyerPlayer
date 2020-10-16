#ifndef EYERLIB_EYERDASHREADERTHREAD_HPP
#define EYERLIB_EYERDASHREADERTHREAD_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer{
    class EyerDASHReaderThread : public EyerThread {
    public:
        EyerDASHReaderThread(EyerString & _mpdUrl, EyerBuffer * dataBuffer);
        ~EyerDASHReaderThread();

        virtual void Run();

    private:
        EyerString & mpdUrl;
        EyerBuffer * dataBuffer = nullptr;
    };
}

#endif //EYERLIB_EYERDASHREADERTHREAD_HPP
