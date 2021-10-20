#ifndef EYERPLAYER_QUEUEBOX_HPP
#define EYERPLAYER_QUEUEBOX_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"

#include "ThreadDecode.hpp"

#include "EyerDecodeQueue/EyerDecodeQueueHeader.hpp"

namespace Eyer
{
    class QueueBox
    {
    public:
        QueueBox();
        ~QueueBox();

        int AddStream(const EyerAVStream & stream);
        int StartDeocder();
        int StopDecoder();

        int GetPacketQueueCacheSize();

        int PutPacket(EyerAVPacket * packet);



        std::mutex mtx;
        std::condition_variable cv;

    private:
        std::vector<EyerAVStream> streamList;
        std::vector<EyerDeocdeQueue *> decoderQueueList;
    };
}

#endif //EYERPLAYER_QUEUEBOX_HPP
