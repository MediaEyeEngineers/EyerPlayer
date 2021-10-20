#include "EyerDeocdeQueueFFmpeg.hpp"

namespace Eyer
{
    EyerDeocdeQueueFFmpeg::EyerDeocdeQueueFFmpeg(const EyerAVStream & stream)
        : EyerDeocdeQueue(stream)
    {

    }

    EyerDeocdeQueueFFmpeg::~EyerDeocdeQueueFFmpeg()
    {
        Stop();
    }

    int EyerDeocdeQueueFFmpeg::Start()
    {
        Stop();
        decodeThread = new FFmpegDecodeThread();
        decodeThread->Start();
        return 0;
    }

    int EyerDeocdeQueueFFmpeg::Stop()
    {
        if(decodeThread != nullptr){
            decodeThread->Stop();
            delete decodeThread;
            decodeThread = nullptr;
        }
        return 0;
    }

    int EyerDeocdeQueueFFmpeg::PutPacket(EyerAVPacket & packet)
    {
        return 0;
    }
}