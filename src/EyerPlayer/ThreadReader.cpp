#include "ThreadReader.hpp"

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

#include "EventControlThread.hpp"

namespace Eyer
{
    ThreadReader::ThreadReader(EyerPlayerContext * _playerContext)
        : playerContext(_playerContext)
    {

    }

    ThreadReader::~ThreadReader()
    {

    }

    void ThreadReader::Run()
    {
        EyerLog("ThreadReader Start\n");

        std::unique_lock<std::mutex> locker(playerContext->commonMut);

        reader = new EyerAVReader(playerContext->url);
        reader->Open();

        EyerAVPacket * packet = nullptr;
        while(!stopFlag){
            if(packet == nullptr){
                packet = new EyerAVPacket();
                int ret = reader->Read(*packet);
                if(ret){
                    // 文件末尾或者读取出错
                    // 报错
                    delete packet;
                    packet = nullptr;
                }
            }

            if(packet != nullptr){
                // EyerLog("Packet PTS: %f\n", packet->GetSecPTS());
                delete packet;
                packet = nullptr;
            }
        }

        if(packet != nullptr){
            delete packet;
            packet = nullptr;
        }

        if(reader != nullptr){
            reader->Close();
            delete reader;
            reader = nullptr;
        }

        EyerLog("ThreadReader End\n");
    }

    int ThreadReader::SetStopFlag(){
        std::unique_lock<std::mutex> locker(playerContext->commonMut);
        stopFlag = 1;

        return 0;
    }

    int ThreadReader::SetStartEventLoopFlag()
    {
        std::unique_lock<std::mutex> locker(playerContext->commonMut);
        eventLoopFlag = 1;
        /*
        std::unique_lock<std::mutex> locker(decoderBox->cvBox.mtx);
        eventLoopFlag = 1;
        decoderBox->cvBox.cv.notify_all();
        */
        return 0;
    }
}