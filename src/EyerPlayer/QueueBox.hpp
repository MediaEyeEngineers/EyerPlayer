#ifndef EYERPLAYER_QUEUEBOX_HPP
#define EYERPLAYER_QUEUEBOX_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "ThreadDecode.hpp"

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
        std::atomic_int packetCacheSize {0};
        std::vector<EyerAVStream> streamList;

        std::vector<ThreadDecode *> decoderList;
    };
}

#endif //EYERPLAYER_QUEUEBOX_HPP
