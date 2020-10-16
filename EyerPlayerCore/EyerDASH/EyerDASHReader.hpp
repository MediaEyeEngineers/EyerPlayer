#ifndef EYERLIB_EYERDASHREADER_HPP
#define EYERLIB_EYERDASHREADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerMPD.hpp"
#include "EyerDASHReaderThread.hpp"

namespace Eyer{
    class EyerDASHReader {
    public:
        EyerDASHReader(const EyerString & _mpdUrl);
        ~EyerDASHReader();

        int SetCacheDir(const EyerString & _cacheUrl);

        int read_packet(void * opaque, uint8_t *buf, int buf_size);
        int seek_packet(void * opaque, int64_t offset, int whence);

    private:
        EyerString mpdUrl;
        EyerString cacheUrl;

        int index = 0;

        EyerDASHReaderThread * readerThread = nullptr;

        EyerBuffer dataBuffer;
    };
}


#endif //EYERLIB_EYERDASHREADER_HPP
