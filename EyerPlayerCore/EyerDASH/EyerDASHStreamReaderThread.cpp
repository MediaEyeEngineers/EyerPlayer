#include "EyerDASHStreamReaderThread.hpp"

#include "EyerNet/EyerNet.hpp"
#include "EyerMPD.hpp"

#include "EyerMP4/EyerMP4.hpp"

namespace Eyer
{
    EyerDASHStreamReaderThread::EyerDASHStreamReaderThread(EyerString & _mpdUrl, int _videoStreamIndex, int _audioStreamIndex, int _startFragmentIndex, BufferQueue * _mp4BufferQueue)
    {
        mpdUrl                  = _mpdUrl;
        videoStreamIndex        = _videoStreamIndex;
        audioStreamIndex        = _audioStreamIndex;

        startFragmentIndex      = _startFragmentIndex;
        endFragmentIndex        = -1;

        mp4BufferQueue          = _mp4BufferQueue;
    }

    EyerDASHStreamReaderThread::~EyerDASHStreamReaderThread()
    {

    }

    int EyerDASHStreamReaderThread::SetEndIndex(int _endFragmentIndex)
    {
        endFragmentIndex = _endFragmentIndex;
        return 0;
    }

    void EyerDASHStreamReaderThread::Run()
    {
        Eyer::EyerSimplestHttp http;
        Eyer::EyerBuffer buffer;
        int ret = http.Get(buffer, mpdUrl);
        if(ret){
            EyerLog("Read mpd file error");
            return;
        }

        Eyer::EyerMPD mpd;
        ret = mpd.LoadMPD(buffer);
        if(ret){
            EyerLog("Read mpd file error");
            return;
        }

        EyerBuffer mp4HeadBuffer = ReadHeadBuffer(mpd);
        MP4Box mp4HeadBox;
        mp4HeadBox.ParseSubBox(mp4HeadBuffer);
        mp4HeadBox.PrintInfo();

        MP4Buffer * mp4Head = new MP4Buffer(mp4HeadBuffer, MP4BufferType::HEAD);
        mp4BufferQueue->Push(mp4Head);

        int index = startFragmentIndex;

        while(!stopFlag) {
            while (mp4BufferQueue->Size() >= 3) {
                Eyer::EyerTime::EyerSleepMilliseconds(100);
                continue;
            }

            if(endFragmentIndex > 0){
                if(index > endFragmentIndex){
                    break;
                }
            }

            {
                EyerString m4vUrl;
                mpd.GetVideoURL(m4vUrl, index, videoStreamIndex);

                Eyer::EyerURLUtil urlUtil(mpdUrl);
                m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

                Eyer::EyerSimplestHttp http;
                Eyer::EyerBuffer m4vBuffer;
                ret = http.Get(m4vBuffer, m4vUrl);
                if (ret) {
                    continue;
                }

                MP4Buffer * mp4Video = new MP4Buffer(m4vBuffer, MP4BufferType::VIDEO);
                mp4BufferQueue->Push(mp4Video);
            }

            {
                EyerString m4vUrl;
                mpd.GetVideoURL(m4vUrl, index, audioStreamIndex);

                Eyer::EyerURLUtil urlUtil(mpdUrl);
                m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

                EyerLog("m4v url: %s\n", m4vUrl.str);
                m4vUrl = EyerString("http://redknot.cn/DASH/./audio/xiaomai_dash") + EyerString::Number(index) + ".m4s";

                Eyer::EyerSimplestHttp http;
                Eyer::EyerBuffer m4vBuffer;
                ret = http.Get(m4vBuffer, m4vUrl);
                if (ret) {
                    continue;
                }

                MP4Buffer * mp4Audio = new MP4Buffer(m4vBuffer, MP4BufferType::AUDIO);
                mp4BufferQueue->Push(mp4Audio);
            }

            index++;
        }
    }

    EyerBuffer EyerDASHStreamReaderThread::ReadHeadBuffer(Eyer::EyerMPD & mpd)
    {
        EyerBuffer headBuf;
        int ret = 0;

        MP4Box videoBox;
        MP4Box audioBox;
        {
            EyerString m4vUrl;
            mpd.GetInitURL(m4vUrl, videoStreamIndex);

            Eyer::EyerURLUtil urlUtil(mpdUrl);
            m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;
            Eyer::EyerBuffer m4vBuffer;
            ret = http.Get(m4vBuffer, m4vUrl);
            if(ret){
                // Http fail
                return headBuf;
            }

            printf("==========Parse==========\n");
            videoBox.ParseSubBox(m4vBuffer);
            // videoBox.PrintInfo();
        }

        {
            EyerString m4vUrl = "http://redknot.cn/DASH/./audio/xiaomai_dashinit.mp4";
            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;

            Eyer::EyerBuffer m4vBuffer;
            ret = http.Get(m4vBuffer, m4vUrl);
            if(ret){
                // Http fail
                return headBuf;
            }
            printf("==========Parse==========\n");
            audioBox.ParseSubBox(m4vBuffer);
            // audioBox.PrintInfo();
        }

        headBuf = MergeVideoAudio(videoBox, audioBox);

        // MergeAllTrack(mpd);

        return headBuf;
    }

    EyerBuffer EyerDASHStreamReaderThread::MergeAllTrack(Eyer::EyerMPD & mpd)
    {
        EyerBuffer resBuf;

        // FTYP

        std::vector<MP4BoxMVHD> mvhdList;
        std::vector<MP4BoxMEHD> mehdList;
        std::vector<MP4BoxTREX> trexList;
        std::vector<MP4Box> trakList;
        std::vector<MP4BoxFTYP> ftypList;

        MP4Box moov(BoxType::MOOV);

        for(int representationIndex=0;representationIndex<4;representationIndex++){
            EyerString m4vUrl;
            mpd.GetInitURL(m4vUrl, representationIndex);

            Eyer::EyerURLUtil urlUtil(mpdUrl);
            m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;
            Eyer::EyerBuffer m4vBuffer;
            int ret = http.Get(m4vBuffer, m4vUrl);
            if(ret){
                // Http fail
                continue;
            }

            printf("==========Parse==========\n");
            MP4Box videoBox;
            videoBox.ParseSubBox(m4vBuffer);
            // videoBox.PrintInfo();

            MP4BoxFTYP * ftypPtr = (MP4BoxFTYP *)videoBox.GetSubBoxPtr(BoxType::FTYP);
            if(ftypPtr == nullptr){
                continue;
            }
            ftypList.push_back(*ftypPtr);

            MP4Box * moovPtr = videoBox.GetSubBoxPtr(BoxType::MOOV);
            if(moovPtr == nullptr){
                continue;
            }
            MP4BoxMVHD * mvhdPtr = (MP4BoxMVHD *)moovPtr->GetSubBoxPtr(BoxType::MVHD);
            if(mvhdPtr == nullptr){
                continue;
            }
            mvhdList.push_back(*mvhdPtr);

            MP4Box * trakPtr = moovPtr->GetSubBoxPtr(BoxType::TRAK);
            if(trakPtr == nullptr){
                continue;
            }
            trakList.push_back(*trakPtr);

            MP4Box * mvexPtr = moovPtr->GetSubBoxPtr(BoxType::MVEX);
            if(mvexPtr == nullptr){
                continue;
            }
            MP4BoxMEHD * mehdPtr = (MP4BoxMEHD *)mvexPtr->GetSubBoxPtr(BoxType::MEHD);
            if(mehdPtr == nullptr){
                continue;
            }
            mehdList.push_back(*mehdPtr);

            MP4BoxTREX * trexPtr = (MP4BoxTREX *)mvexPtr->GetSubBoxPtr(BoxType::TREX);
            if(trexPtr == nullptr){
                continue;
            }
            trexList.push_back(*trexPtr);
        }



        {
            mvhdList[0].next_track_ID = 5;
            moov.AddSubBox(mvhdList[0]);
            for(int i = 0; i < trakList.size(); i++){
                // moov.AddSubBox(trakList[i]);
            }
            MP4Box mvex(BoxType::MVEX);
            {
                mvex.AddSubBox(mehdList[0]);
                for(int i=0;i<trexList.size();i++){
                    trexList[i].track_ID = i + 1;
                    mvex.AddSubBox(trexList[i]);
                }
            }
            moov.AddSubBox(mvex);

            for (int i = 0; i < trakList.size(); i++) {
                moov.AddSubBox(trakList[i]);
            }
        }

        resBuf.Append(ftypList[0].Serialize());
        resBuf.Append(moov.Serialize());

        return resBuf;
    }

    EyerBuffer EyerDASHStreamReaderThread::MergeVideoAudio(MP4Box & videoBox, MP4Box & audioBox)
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
            MP4BoxMVHD mvhd = *videoMvhdPtr;
            moov.AddSubBox(mvhd);

            moov.AddSubBox(videoTrakPtr);
            moov.AddSubBox(audioTrakPtr);

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
            moov.AddSubBox(mvex);
        }

        buffer.Append(ftyp.Serialize());
        buffer.Append(moov.Serialize());

        return buffer;
    }
}