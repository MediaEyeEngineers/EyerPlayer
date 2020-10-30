#include "EyerDASHReaderThread.hpp"
#include "EyerNet/EyerNet.hpp"
#include "EyerMPD.hpp"

#include "EyerMP4/EyerMP4.hpp"

namespace Eyer
{
    EyerDASHReaderThread::EyerDASHReaderThread(EyerString & _mpdUrl, EyerBuffer * _dataBuffer)
        : mpdUrl(_mpdUrl)
    {
        dataBuffer = _dataBuffer;
    }

    EyerDASHReaderThread::~EyerDASHReaderThread()
    {

    }

    void EyerDASHReaderThread::Run()
    {
        Eyer::EyerSimplestHttp http;
        Eyer::EyerBuffer buffer;
        int ret = http.Get(buffer, mpdUrl);
        if(ret){
            EyerLog("Read mpd file error A");
            return;
        }

        Eyer::EyerMPD mpd;
        ret = mpd.LoadMPD(buffer);
        if(ret){
            EyerLog("Read mpd file error B");
            return;
        }

        mpd.PrintInfo();


        int representationIndex = 0;

        // get video init buffer
        MP4Box videoBox;
        MP4Box audioBox;

        Eyer::EyerBuffer m4vBuffer;
        {
            EyerString m4vUrl;
            mpd.GetInitURL(m4vUrl, representationIndex);

            Eyer::EyerURLUtil urlUtil(mpdUrl);
            m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;


            ret = http.Get(m4vBuffer, m4vUrl);
            if(ret){
                // Http fail
                return;
            }

            printf("==========Parse==========\n");
            videoBox.ParseSubBox(m4vBuffer);
            videoBox.PrintInfo();
        }

        Eyer::EyerBuffer m4aBuffer;
        {
            EyerString m4vUrl = "http://redknot.cn/DASH/./audio/xiaomai_dashinit.mp4";
            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;


            ret = http.Get(m4aBuffer, m4vUrl);
            if(ret){
                // Http fail
                return;
            }

            printf("==========Parse==========\n");
            audioBox.ParseSubBox(m4aBuffer);
            audioBox.PrintInfo();
        }

        printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        EyerBuffer fmp4InitBuffer = MergeVideoAudio(videoBox, audioBox);
        MP4Box fmp4InitBox;
        fmp4InitBox.ParseSubBox(fmp4InitBuffer);
        fmp4InitBox.PrintInfo();

        // dataBuffer->Append(fmp4InitBuffer);
        dataBuffer->Append(m4vBuffer);

        int index = 1;
        while(!stopFlag){
            EyerTime::EyerSleepMilliseconds(1);
            if(dataBuffer->GetLen() >= 1024 * 1024 * 1){
                continue;
            }

            {
                EyerString m4vUrl;
                mpd.GetVideoURL(m4vUrl, index, representationIndex);

                Eyer::EyerURLUtil urlUtil(mpdUrl);
                m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

                // EyerLog("m4v url: %s\n", m4vUrl.str);
                // m4vUrl = EyerString("https:/redknot.cn/DASH/./audio/xiaomai_dash") + EyerString::Number(index) + ".m4s";

                Eyer::EyerSimplestHttp http;
                Eyer::EyerBuffer m4vBuffer;
                ret = http.Get(m4vBuffer, m4vUrl);
                if(ret){
                    continue;
                }

                dataBuffer->Append(m4vBuffer);
            }

            /*
            {
                EyerString m4vUrl;
                mpd.GetVideoURL(m4vUrl, index, representationIndex);

                Eyer::EyerURLUtil urlUtil(mpdUrl);
                m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

                m4vUrl = EyerString("http://redknot.cn/DASH/./audio/xiaomai_dash") + EyerString::Number(index) + ".m4s";
                EyerLog("m4v url: %s\n", m4vUrl.str);

                Eyer::EyerSimplestHttp http;
                Eyer::EyerBuffer m4vBuffer;
                ret = http.Get(m4vBuffer, m4vUrl);
                if(ret){
                    continue;
                }

                dataBuffer->Append(m4vBuffer);
            }
            */


            index++;
        }
    }

    EyerBuffer EyerDASHReaderThread::MergeVideoAudio(MP4Box & videoBox, MP4Box & audioBox)
    {
        EyerBuffer buffer;

        // AV Moov
        MP4Box * audioMoovPtr = audioBox.GetSubBoxPtr(BoxType::MOOV);
        if(audioMoovPtr == nullptr){
            return buffer;
        }
        MP4Box * videoMoovPtr = videoBox.GetSubBoxPtr(BoxType::MOOV);
        if(videoMoovPtr == nullptr){
            return buffer;
        }

        // AV Mvhd
        MP4BoxMVHD * audioMvhdPtr = (MP4BoxMVHD *)audioMoovPtr->GetSubBoxPtr(BoxType::MVHD);
        if(audioMvhdPtr == nullptr){
            return buffer;
        }
        MP4BoxMVHD * videoMvhdPtr = (MP4BoxMVHD *)videoMoovPtr->GetSubBoxPtr(BoxType::MVHD);
        if(videoMvhdPtr == nullptr){
            return buffer;
        }

        // AV Trak
        MP4Box * audioTrakPtr = audioMoovPtr->GetSubBoxPtr(BoxType::TRAK);
        if(audioTrakPtr == nullptr){
            return buffer;
        }
        MP4Box * videoTrakPtr = videoMoovPtr->GetSubBoxPtr(BoxType::TRAK);
        if(videoTrakPtr == nullptr){
            return buffer;
        }

        // AV Mvex
        MP4Box * audioMvexPtr = audioMoovPtr->GetSubBoxPtr(BoxType::MVEX);
        if(audioMvexPtr == nullptr){
            return buffer;
        }
        MP4Box * videoMvexPtr = videoMoovPtr->GetSubBoxPtr(BoxType::MVEX);
        if(videoMvexPtr == nullptr){
            return buffer;
        }

        // AV Mehd
        MP4BoxMEHD * audioMehdPtr = (MP4BoxMEHD *)audioMvexPtr->GetSubBoxPtr(BoxType::MEHD);
        if(audioMehdPtr == nullptr){
            return buffer;
        }
        MP4BoxMEHD * videoMehdPtr = (MP4BoxMEHD *)videoMvexPtr->GetSubBoxPtr(BoxType::MEHD);
        if(videoMehdPtr == nullptr){
            return buffer;
        }

        // AV Trex
        MP4BoxTREX * audioTrexPtr = (MP4BoxTREX *)audioMvexPtr->GetSubBoxPtr(BoxType::TREX);
        if(audioTrexPtr == nullptr){
            return buffer;
        }
        MP4BoxTREX * videoTrexPtr = (MP4BoxTREX *)videoMvexPtr->GetSubBoxPtr(BoxType::TREX);
        if(videoTrexPtr == nullptr){
            return buffer;
        }


        // FTYP
        MP4BoxFTYP ftyp;
        MP4BoxFTYP * ftypPtr = (MP4BoxFTYP *)videoBox.GetSubBoxPtr(BoxType::FTYP);
        ftyp = *ftypPtr;

        // Moov
        MP4Box moov(BoxType::MOOV);
        {
            // Mvhd
            MP4BoxMVHD mvhd = *audioMvhdPtr;
            moov.AddSubBox(mvhd);

            MP4Box mvex(BoxType::MVEX);
            {
                {
                    MP4BoxMEHD mehd;
                    if(videoMehdPtr->Get_fragment_duration() > audioMehdPtr->Get_fragment_duration()){
                        mehd = *videoMehdPtr;
                    }
                    else{
                        mehd = *audioMehdPtr;
                    }
                    mvex.AddSubBox(mehd);
                }
                {
                    // Video Trex
                    mvex.AddSubBox(videoTrexPtr);
                }
                {
                    // Audio Trex
                    mvex.AddSubBox(audioTrexPtr);
                }
            }

            moov.AddSubBox(videoTrakPtr);
            moov.AddSubBox(audioTrakPtr);

            moov.AddSubBox(mvex);
        }

        buffer.Append(ftyp.Serialize());
        buffer.Append(moov.Serialize());

        return buffer;
    }
}