#include "EyerDASHReader.hpp"
#include "EyerNet/EyerNet.hpp"
#include "EyerMPD.hpp"

namespace Eyer
{
    EyerDASHReader::EyerDASHReader(const EyerString & _mpdUrl)
    {
        mpdUrl = _mpdUrl;
    }

    EyerDASHReader::~EyerDASHReader()
    {
        for(int i=0;i<streamList.size();i++){
            delete streamList[i];
        }
    }

    int EyerDASHReader::SwitchStream(int streamId)
    {
        EyerDASHStream * stream = FindCurrentStream();
        stream->SetEndIndex(currentIndex + 3);
        return 0;
    }

    int EyerDASHReader::CreateStream(int streamId)
    {
        printf("EyerDASHStream Start\n");
        currentStream = new EyerDASHStream(mpdUrl, streamId, 1, currentIndex);
        currentStream->StartLoad();
        streamList.push_back(currentStream);

        return 0;
    }

    int EyerDASHReader::read_packet(uint8_t * buf, int buf_size)
    {
        if(cacheBuf.GetLen() > 0){
            int size = buf_size;
            if(size > cacheBuf.GetLen()){
                size = cacheBuf.GetLen();
            }

            EyerBuffer b;
            cacheBuf.CutOff(b, size);
            b.GetBuffer(buf);

            return size;
        }

        EyerDASHStream * stream = FindCurrentStream();
        // EyerDASHStream * stream = currentStream;
        if(stream == nullptr){
            return -1;
        }

        while(stream->GetMP4BuffeQueueSize() <= 0){
            // TODO 用观察者模式重写
            Eyer::EyerTime::EyerSleepMilliseconds(10);
            continue;
        }

        MP4Buffer * mp4Buffer = nullptr;
        stream->PopMP4Buffer(&mp4Buffer);
        if(mp4Buffer != nullptr){
            EyerBuffer buffer = mp4Buffer->GetBuffer();
            cacheBuf.Append(buffer);

            if(mp4Buffer->GetType() == MP4BufferType::HEAD){
            }
            if(mp4Buffer->GetType() == MP4BufferType::AUDIO){
            }
            if(mp4Buffer->GetType() == MP4BufferType::VIDEO){
                currentIndex++;
            }

            delete mp4Buffer;
            mp4Buffer = nullptr;
        }

        if(cacheBuf.GetLen() > 0){
            int size = buf_size;
            if(size > cacheBuf.GetLen()){
                size = cacheBuf.GetLen();
            }

            EyerBuffer b;
            cacheBuf.CutOff(b, size);
            b.GetBuffer(buf);

            return size;
        }

        return 0;
    }

    int EyerDASHReader::seek_packet(int64_t offset, int whence)
    {

        return 0;
    }

    EyerDASHStream * EyerDASHReader::FindCurrentStream()
    {
        EyerDASHStream * stream = nullptr;
        printf("Size: %d\n", streamList.size());
        printf("Index: %d\n", currentIndex);
        for(int i=0;i<streamList.size();i++){
            EyerDASHStream * _stream = streamList[i];
            int startIndex = _stream->GetStartIndex();
            int endIndex = _stream->GetEndIndex();
            printf("Start Index: %d, End Index: %d\n", startIndex, endIndex);
        }
        for(int i=0;i<streamList.size();i++){
            EyerDASHStream * _stream = streamList[i];
            int startIndex = _stream->GetStartIndex();
            int endIndex = _stream->GetEndIndex();

            if(endIndex > 0){
                if(currentIndex > endIndex){
                    continue;
                }
            }
            if(currentIndex < startIndex){
                continue;
            }

            stream = _stream;
        }

        return stream;
    }
}