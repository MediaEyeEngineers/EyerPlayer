#ifndef EYERPLAYER_AVDECODEQUEUEBOX_HPP
#define EYERPLAYER_AVDECODEQUEUEBOX_HPP

#include <vector>

#include "EyerAV/EyerAV.hpp"

#include "EyerDecodeQueue/EyerDecodeQueueHeader.hpp"

namespace Eyer
{
    class AVDecodeQueueBox
    {
    public:
        AVDecodeQueueBox();
        ~AVDecodeQueueBox();

        int AddStream(const EyerAVStream & stream);
        int ClearAllStream();

        int StartAllDecoder();
        int StopAllDecoder();

    private:
        std::vector<EyerAVStream> streamList;
        std::vector<EyerDecodeQueueBase *> decoderList;
    };
}

#endif //EYERPLAYER_AVDECODEQUEUEBOX_HPP
