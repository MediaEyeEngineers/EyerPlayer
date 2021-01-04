#ifndef EYERLIB_EYERDASHREADER_HPP
#define EYERLIB_EYERDASHREADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerMPD.hpp"
#include "EyerDASHReaderThread.hpp"
#include "EyerDASHStream.hpp"

namespace Eyer{
    class EyerDASHReader {
    public:
        EyerDASHReader(const EyerString & _mpdUrl);
        ~EyerDASHReader();

        int SwitchStream(int streamId);
        int CreateStream(int streamId);

        int read_packet(uint8_t *buf, int buf_size);
        int seek_packet(int64_t offset, int whence);

    private:
        EyerString mpdUrl;

        std::vector<EyerDASHStream *> streamList;

        int currentIndex = 1;
        EyerBuffer cacheBuf;

        EyerDASHStream * FindCurrentStream();
        EyerDASHStream * currentStream = nullptr;
    };
}


#endif //EYERLIB_EYERDASHREADER_HPP
