#ifndef EYERLIB_EYERAVREADER_HPP
#define EYERLIB_EYERAVREADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVPacket.hpp"
#include "EyerAVStream.hpp"

namespace Eyer
{
    class EyerAVReaderPrivate;

    class EyerAVReader {
    public:
        EyerAVReader(EyerString _path);
        ~EyerAVReader();

        int Open();
        int Close();

        double GetDuration();

        int GetStreamCount();
        int GetStream(EyerAVStream & stream, int index);

        int GetTimebase(EyerAVRational & timebase, int streamIndex);

        int Seek(double time);

        int Read(EyerAVPacket & packet);

        int GetAudioStreamIndex() const;
        int GetVideoStreamIndex() const;

    private:
        EyerAVReader(const EyerAVReader & reader) = delete;
        EyerAVReader & operator = (const EyerAVReader & reader) = delete;

    public:
        EyerAVReaderPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVREADER_HPP
