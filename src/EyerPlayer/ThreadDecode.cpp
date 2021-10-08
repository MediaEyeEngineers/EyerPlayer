#include "ThreadDecode.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    ThreadDecode::ThreadDecode(const Eyer::EyerAVStream & _stream, Eyer::EyerObserverQueue<EyerAVPacket *> * _packetQueue)
    {
        stream = _stream;
        packetQueue = _packetQueue;
    }

    ThreadDecode::~ThreadDecode()
    {

    }

    void ThreadDecode::Run()
    {
        EyerLog("ThreadDecode Start\n");
        // 该线程用于解码

        // 初始化解码器
        Eyer::EyerAVDecoder decoder;
        int ret = decoder.Init(stream);
        if(ret){
            EyerLog("Init Decoder Fail\n");
        }

        while(!stopFlag) {
            if(packetQueue->Size() > 0){
                EyerAVPacket * packet = nullptr;
                packetQueue->FrontPop(packet);
                if(packet != nullptr){
                    decoder.SendPacket(*packet);
                    while(1){
                        EyerAVFrame * frame = new EyerAVFrame();
                        ret = decoder.RecvFrame(*frame);
                        if(ret){
                            if(frame != nullptr){
                                delete frame;
                                frame = nullptr;
                            }
                            break;
                        }
                        EyerLog("Frame PTS: %f\n", frame->GetSecPTS());
                        if(frame != nullptr){
                            delete frame;
                            frame = nullptr;
                        }
                    }

                    delete packet;
                    packet = nullptr;
                }
            }
        }

        EyerLog("ThreadDecode End\n");
    }
}