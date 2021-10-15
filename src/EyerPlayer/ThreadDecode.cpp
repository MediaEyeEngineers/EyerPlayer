#include "ThreadDecode.hpp"

#include "EyerCore/EyerCore.hpp"
#include "QueueBox.hpp"
#include "EyerAV/EyerAV.hpp"

namespace Eyer
{
    ThreadDecode::ThreadDecode(const Eyer::EyerAVStream & _stream, QueueBox * _queueBox)
        : stream(_stream)
        , queueBox(_queueBox)
    {
    }

    ThreadDecode::~ThreadDecode()
    {

    }

    int ThreadDecode::GetStreamId()
    {
        return stream.GetStreamId();
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

        }

        EyerLog("ThreadDecode End\n");
    }
}