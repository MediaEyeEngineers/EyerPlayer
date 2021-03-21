#include "EyerOpenSL.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    void bufferQueueCallback(SLAndroidSimpleBufferQueueItf bufferQueue, void *pContext) {
        EyerAVFrame * audioFrame = nullptr;

        ((EyerOpenSL *)pContext)->GetFrame(&audioFrame);
        if(audioFrame != nullptr){
            int bufferLen = audioFrame->GetAudioPackedData(nullptr);

            unsigned char * buf = (unsigned char *)malloc(bufferLen);
            audioFrame->GetAudioPackedData(buf);

            (*bufferQueue)->Enqueue(bufferQueue, buf, bufferLen);
            free(buf);
            delete audioFrame;
        }
        else{
            int len = 128;
            unsigned char * buf = (unsigned char *)malloc(len);
            memset(buf, 0, len);
            (*bufferQueue)->Enqueue(bufferQueue, buf, len);
            free(buf);
        }
    }


    EyerOpenSL::EyerOpenSL(MediaInfo & mediaInfo)
    {
        audioFrameQueue = new AVFrameQueue();

        EyerLog("createEngine()");
        SLresult result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
        if(result != SL_RESULT_SUCCESS) {
            EyerLog("slCreateEngine failed, result=%d", result);
        }
        result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
        if(result != SL_RESULT_SUCCESS) {
            EyerLog("engineObject Realize failed, result=%d", result);
        }
        result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &(engineEngine));
        if(result != SL_RESULT_SUCCESS) {
            EyerLog("engineObject GetInterface failed, result=%d", result);
        }







        SLObjectItf mix = nullptr;
        result = (*engineEngine)->CreateOutputMix(engineEngine, &mix, 0, 0, 0);
        if(result != SL_RESULT_SUCCESS) {
            EyerLog("CreateOutputMix failed, result=%d", result);
        }

        result = (*mix)->Realize(mix, SL_BOOLEAN_FALSE);
        if(result != SL_RESULT_SUCCESS) {
            EyerLog("(*mix)->Realize(mix, SL_BOOLEAN_FALSE); failed, result=%d", result);
        }

        SLDataLocator_OutputMix outmix = {SL_DATALOCATOR_OUTPUTMIX, mix};
        SLDataSink audioSink = {&outmix, 0};




        SLDataLocator_AndroidSimpleBufferQueue que = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 10};
        SLDataFormat_PCM pcm = {0};

        pcm.formatType      = SL_DATAFORMAT_PCM;
        pcm.numChannels     = mediaInfo.audioStream.audioChannels;
        pcm.samplesPerSec   = mediaInfo.audioStream.audioSampleRate * 1000;
        pcm.bitsPerSample   = SL_PCMSAMPLEFORMAT_FIXED_32;
        pcm.containerSize   = SL_PCMSAMPLEFORMAT_FIXED_32;
        pcm.channelMask     = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
        pcm.endianness      = SL_BYTEORDER_LITTLEENDIAN;

        SLDataSource ds = {&que, &pcm};










        const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE};
        const SLboolean req[] = {SL_BOOLEAN_TRUE};

        result = (*engineEngine)->CreateAudioPlayer(engineEngine, &player, &ds, &audioSink, sizeof(ids)/sizeof(SLInterfaceID), ids, req);
        if(result != SL_RESULT_SUCCESS) {
            EyerLog("CreateAudioPlayer failed, result=%d", result);
        }

        (*player)->Realize(player, SL_BOOLEAN_FALSE);
        result = (*player)->GetInterface(player, SL_IID_PLAY, &iplayer);
        if(result != SL_RESULT_SUCCESS) {
            EyerLog("(*player)->GetInterface(player, SL_IID_PLAY, &iplayer) failed, result=%d", result);
        }

        result = (*player)->GetInterface(player, SL_IID_BUFFERQUEUE, &pcmQue);
        if(result != SL_RESULT_SUCCESS) {
            EyerLog("(*player)->GetInterface(player, SL_IID_BUFFERQUEUE, &pcmQue) failed, result=%d", result);
        }

        (*pcmQue)->RegisterCallback(pcmQue, bufferQueueCallback, this);
        (*iplayer)->SetPlayState(iplayer, SL_PLAYSTATE_PLAYING);
        (*pcmQue)->Enqueue(pcmQue, "", 1);
    }

    EyerOpenSL::~EyerOpenSL()
    {
        (*iplayer)->SetPlayState(iplayer, SL_PLAYSTATE_STOPPED);

        ClearAllCache();

        if(audioFrameQueue != nullptr){
            delete audioFrameQueue;
            audioFrameQueue = nullptr;
        }
    }

    int EyerOpenSL::Print()
    {
        EyerLog("Miaomiao\n");
        return 0;
    }

    int EyerOpenSL::PutFrame(EyerAVFrame * frame)
    {
        return audioFrameQueue->Push(frame);
    }

    int EyerOpenSL::GetFrame(EyerAVFrame * * frame)
    {
        // EyerLog("Audio Queue Size: %d\n", audioFrameQueue->Size());
        while(audioFrameQueue->Size() >= 2){
            EyerAVFrame * f = nullptr;
            audioFrameQueue->FrontPop(&f);
            if(f != nullptr){
                delete f;
            }
        }
        return audioFrameQueue->FrontPop(frame);
    }

    int EyerOpenSL::ClearAllCache()
    {
        while(audioFrameQueue->Size() > 0){
            EyerAVFrame * f = nullptr;
            audioFrameQueue->FrontPop(&f);
            if(f != nullptr){
                delete f;
            }
        }

        return 0;
    }
}