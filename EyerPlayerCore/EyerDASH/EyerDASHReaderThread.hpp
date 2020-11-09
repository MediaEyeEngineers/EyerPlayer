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

        int DataBufferChange();

    private:
        EyerString & mpdUrl;
        EyerBuffer * dataBuffer = nullptr;

        std::mutex mtx;
        std::condition_variable cv;

        EyerBuffer MergeVideoAudio(MP4Box & videoBox, MP4Box & audioBox);
    };
}

#endif //EYERLIB_EYERDASHREADERTHREAD_HPP
