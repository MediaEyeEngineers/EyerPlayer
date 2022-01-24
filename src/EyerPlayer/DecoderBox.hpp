#ifndef EYERPLAYERANDROID_DECODERBOX_HPP
#define EYERPLAYERANDROID_DECODERBOX_HPP

#include "EyerAV/EyerAV.hpp"
#include "EyerThread/EyerThreadHeader.hpp"
#include "EyerDecodeQueue/EyerDecodeQueueHeader.hpp"

namespace Eyer
{
    class DecoderBox
    {
    public:
        DecoderBox();
        ~DecoderBox();

        int AddStream(const EyerAVStream & stream);

        int StartDeocder();
        int StopDecoder();

        int PutPacket(EyerAVPacket * packet);
        int GetPacketCacheSize();

        int GetVideoStreamIndex();
        int GetAudioStreamIndex();

        EyerConditionVariableBox cvBox;

    private:
        std::vector<EyerAVStream> streamList;
        std::vector<EyerDeocderQueue *> decoderList;
    };
}

#endif //EYERPLAYERANDROID_DECODERBOX_HPP
