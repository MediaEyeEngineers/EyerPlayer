//
// Created by redknot on 2020/8/23.
//

#ifndef EYERPLAYER_EYEROPENSL_HPP
#define EYERPLAYER_EYEROPENSL_HPP

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <EyerAV/EyerAVAV.hpp>
#include <EyerPlayer/PlayerQueueManager.hpp>

namespace Eyer{

    class EyerOpenSLCallback
    {
    public:
        virtual int pcmCallback(Eyer::EyerAVFrame * frame);
    };

    class EyerOpenSL {
    public:
        EyerOpenSL();
        ~EyerOpenSL();

        int Print();

        int ClearAllCache();

        int PutFrame(EyerAVFrame * frame);
        int GetFrame(EyerAVFrame * * frame);
    private:
        SLObjectItf engineObject = nullptr;
        SLEngineItf engineEngine = nullptr;


        SLObjectItf player = nullptr;
        SLPlayItf iplayer = nullptr;
        SLAndroidSimpleBufferQueueItf pcmQue = nullptr;


        AVFrameQueue * audioFrameQueue = nullptr;
    };
}

#endif //EYERPLAYER_EYEROPENSL_HPP
