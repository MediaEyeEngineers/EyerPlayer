//
// Created by redknot on 2020/3/22.
//

#include "EyerAV.hpp"

namespace Eyer
{
    EyerAVAudioFrameUtil::EyerAVAudioFrameUtil()
    {

    }

    EyerAVAudioFrameUtil::~EyerAVAudioFrameUtil()
    {
        for(int i=0;i<frameList.getLength();i++){
            EyerAVFrameWeight * fw = nullptr;
            frameList.find(i, fw);
            if(fw != nullptr){
                delete fw;
            }
        }
        frameList.clear();
    }

    int EyerAVAudioFrameUtil::AddAudioFrame(EyerAVFrame & frame, float weight)
    {
        EyerAVFrameWeight * fw = new EyerAVFrameWeight(frame, weight);
        frameList.insertBack(fw);

        return 0;
    }

    int EyerAVAudioFrameUtil::MergeAudioFrame(EyerAVFrame & outFrame)
    {
        int maxChannel = outFrame.GetChannels();

        for(int channelIndex=0; channelIndex<maxChannel; channelIndex++){
            int channelDataLen = outFrame.GetPerSampleSize() * outFrame.GetNBSamples();
            for(int dataIndex=0; dataIndex < channelDataLen / 4; dataIndex++){
                // EyerLog("Com Data Index : %d\n", dataIndex);
                float data = 0.0f;
                for(int i=0;i<frameList.getLength();i++){
                    EyerAVFrameWeight * fw = nullptr;
                    frameList.find(i, fw);
                    if(fw != nullptr){
                        float a = fw->frame->GetAudioFloatData(channelIndex, dataIndex);
                        data += a * fw->weight;
                    }
                }

                outFrame.SetAudioFloatData(channelIndex, dataIndex, data);
            }
        }
        
        return 0;
    }
}