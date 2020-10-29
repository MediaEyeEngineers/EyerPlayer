#ifndef EYERLIB_EYERDASHREADERTHREAD_HPP
#define EYERLIB_EYERDASHREADERTHREAD_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

namespace Eyer{
    class EyerDASHReaderThread : public EyerThread {
    public:
        EyerDASHReaderThread(EyerString & _mpdUrl, EyerBuffer * dataBuffer);
        ~EyerDASHReaderThread();

        virtual void Run();

    private:
        EyerString & mpdUrl;
        EyerBuffer * dataBuffer = nullptr;

        EyerBuffer MergeVideoAudio(MP4Box & videoBox, MP4Box & audioBox);
    };
}

#endif //EYERLIB_EYERDASHREADERTHREAD_HPP
