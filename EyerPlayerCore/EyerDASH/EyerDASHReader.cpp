#include "EyerDASHReader.hpp"
#include "EyerNet/EyerNet.hpp"
#include "EyerMPD.hpp"

namespace Eyer
{
    EyerDASHReader::EyerDASHReader(const EyerString & _mpdUrl)
    {
        mpdUrl = _mpdUrl;
        readerThread = new EyerDASHReaderThread(mpdUrl, &dataBuffer);
        readerThread->Start();
    }

    EyerDASHReader::~EyerDASHReader()
    {
        if(readerThread != nullptr){
            readerThread->Stop();
            delete readerThread;
            readerThread = nullptr;
        }
    }

    int EyerDASHReader::SetCacheDir(const EyerString & _cacheUrl)
    {
        cacheUrl = _cacheUrl;
        return 0;
    }

    int EyerDASHReader::read_packet(void * opaque, uint8_t * buf, int buf_size)
    {
        printf("Len: %d\n", dataBuffer.GetLen());

        while(1){
            EyerTime::EyerSleepMilliseconds(1);
            if(dataBuffer.GetLen() > 0){
                break;
            }
        }

        if(dataBuffer.GetLen() > 0){
            EyerBuffer buffer;
            int len = dataBuffer.GetLen();
            if(buf_size <= len){
                len = buf_size;
            }
            dataBuffer.CutOff(buffer, len);

            buffer.GetBuffer(buf);

            return len;
        }

        return -1;
    }

    int EyerDASHReader::seek_packet(void * opaque, int64_t offset, int whence)
    {
        return 0;
    }
}