#include "EyerAVTranscode.hpp"

#include "EyerAVReader.hpp"
#include "EyerAVWriter.hpp"
#include "EyerAVDecoderBox.hpp"

namespace Eyer
{
    EyerAVTranscode::EyerAVTranscode(const EyerString & _srcPath, const EyerString & _targetPath, const EyerAVTranscodeParams & _params)
        : srcPath(_srcPath)
        , targetPath(_targetPath)
        , params(_params)
        , videoReader(_srcPath)
        , audioReader(_srcPath)
        , writer(_targetPath)
        , decoderBox(_srcPath)
    {

    }

    EyerAVTranscode::~EyerAVTranscode()
    {

    }

    int EyerAVTranscode::Transcode()
    {
        writer.Open();

        InitEncoder(writer);
        writer.WriteHand();

        InitDeocder();

        // 如果有音频
        if(decoderAudioStreamIndex >= 0){
            resample.Init(
                    EyerAVChannelLayout::CH_LAYOUT_STEREO,
                    EyerAVSampleFormat::SAMPLE_FMT_FLTP,
                    44100,

                    EyerAVChannelLayout::CH_LAYOUT_STEREO,
                    EyerAVSampleFormat::SAMPLE_FMT_FLTP,
                    audioDecoder.GetSampleRate()
            );
        }


        frameCount = videoDuration * params.fps;
        EyerLog("FrameCount: %lld\n", frameCount);

        // 进行间隔编码，音视频交错
        long frameOffset = 0;
        double limitTime = 0.0;
        while(1){
            limitTime += 0.5;

            int retAudio = -1;
            int retVideo = -1;

            if(params.careVideo){
                retVideo = TranscodeVideo(limitTime, frameOffset);
            }

            if(params.careAudio){
                retAudio = TranscodeAudio(limitTime);
            }

            if(retAudio != 0 && retVideo != 0){
                break;
            }
            // EyerLog("Time: %f\n", limitTime);
        }

        // 清空视频编码器
        if(params.careVideo){
            videoEncoder.SendFrameNull();
            while(1){
                EyerAVPacket packet;
                int ret = videoEncoder.RecvPacket(packet);
                if(ret){
                    break;
                }
                packet.SetStreamIndex(encoderVideoStreamIndex);
                packet.RescaleTs(videoEncoder.GetTimebase(), writer.GetTimebase(encoderVideoStreamIndex));
                writer.WritePacket(packet);
            }
        }


        // 清空重采样器
        if(params.careAudio) {
            resample.PutAVFrameNULL();
            while (1) {
                EyerAVFrame frame;
                int ret = resample.GetFrame(frame, audioEncoder.GetFrameSize());
                if (ret) {
                    break;
                }
                // audioEncoder.SendFrame(frame);
                EyerLog("....Clear Sample\n");
            }
            EyerAVFrame frame;
            int ret = resample.GetLastFrame(frame, audioEncoder.GetFrameSize());
            if (!ret) {
                frame.SetPTS(audioOffset);
                audioOffset += audioEncoder.GetFrameSize();
                // audioEncoder.SendFrame(frame);
                EyerLog("....Clear Sample WWW\n");
            }

            // 清空音频编码器
            audioEncoder.SendFrameNull();
            while (1) {
                EyerAVPacket packet;
                int ret = audioEncoder.RecvPacket(packet);
                if (ret) {
                    break;
                }
                packet.SetStreamIndex(encoderAudioStreamIndex);
                packet.RescaleTs(audioEncoder.GetTimebase(), writer.GetTimebase(encoderAudioStreamIndex));
                writer.WritePacket(packet);
            }
        }

        UninitDeocder();

        writer.WriteTrailer();
        writer.Close();

        return 0;
    }

    int EyerAVTranscode::InitDeocder()
    {
        {
            videoReader.Open();
            decoderVideoStreamIndex = videoReader.GetVideoStreamIndex();
            if(decoderVideoStreamIndex >= 0){
                EyerAVStream stream = videoReader.GetStream(decoderVideoStreamIndex);
                videoDuration = stream.GetDuration();
                videoDeocder.Init(stream);
                // TODO 判断创建失败
            }
        }
        {
            audioReader.Open();
            decoderAudioStreamIndex = audioReader.GetAudioStreamIndex();
            if(decoderAudioStreamIndex >= 0){
                EyerAVStream stream = audioReader.GetStream(decoderAudioStreamIndex);
                audioDecoder.Init(stream);
            }
        }
        return 0;
    }

    int EyerAVTranscode::UninitDeocder()
    {
        videoReader.Close();
        audioReader.Close();
        return 0;
    }

    int EyerAVTranscode::TranscodeAudio(double limitTime)
    {
        while(1){
            EyerAVPacket packet;
            int ret = audioReader.Read(packet);
            if(ret){
                // 清空解码器
                audioDecoder.SendPacketNull();
                while(1){
                    EyerAVFrame frame;
                    ret = audioDecoder.RecvFrame(frame);
                    if(ret){
                        break;
                    }
                    EyerLog("Clear Audio Decoder\n");
                    EncodeAudio(frame);
                }
                return -1;
            }
            if(packet.GetStreamIndex() != decoderAudioStreamIndex){
                continue;
            }

            audioDecoder.SendPacket(packet);
            double lastFrameTime = 0.0;
            while(1){
                EyerAVFrame frame;
                ret = audioDecoder.RecvFrame(frame);
                if(ret){
                    break;
                }

                // 重采样
                resample.PutAVFrame(frame);
                while(1){
                    EyerAVFrame frameOut;
                    ret = resample.GetFrame(frameOut, audioEncoder.GetFrameSize());
                    if(ret){
                        break;
                    }
                    frameOut.SetPTS(audioOffset);
                    audioOffset += audioEncoder.GetFrameSize();
                    EncodeAudio(frameOut);
                }
                lastFrameTime = frame.GetSecPTS();
            }
            if(lastFrameTime > limitTime){
                return 0;
            }
        }
        return 0;
    }

    int EyerAVTranscode::TranscodeVideo(double limitTime, long & frameOffset)
    {
        if(frameOffset >= frameCount){
            return -1;
        }

        while(1){
            double pts = frameOffset * 1.0 / params.fps;

            EyerAVFrame frame;
            int ret = decoderBox.GetFrame(frame, pts);
            if(ret){
                return -1;
            }

            EyerAVFrame distFrame;
            frame.Scale(distFrame, EyerAVPixelFormat::YUV420P, params.targetWidth, params.targetHeight);

            distFrame.SetPTS(pts * 1000);

            videoEncoder.SendFrame(distFrame);
            while (1){
                EyerAVPacket outPacket;
                int ret = videoEncoder.RecvPacket(outPacket);
                if(ret){
                    break;
                }

                outPacket.SetStreamIndex(encoderVideoStreamIndex);
                outPacket.RescaleTs(videoEncoder.GetTimebase(), writer.GetTimebase(encoderVideoStreamIndex));
                writer.WritePacket(outPacket);
            }

            if(pts > limitTime){
                frameOffset++;
                return 0;
            }

            frameOffset++;
        }

        return 0;
    }

    int EyerAVTranscode::EncodeAudio(EyerAVFrame & frame)
    {
        audioEncoder.SendFrame(frame);
        while (1){
            EyerAVPacket packet;
            int ret = audioEncoder.RecvPacket(packet);
            if(ret){
                break;
            }

            packet.SetStreamIndex(encoderAudioStreamIndex);
            packet.RescaleTs(audioEncoder.GetTimebase(), writer.GetTimebase(encoderAudioStreamIndex));
            writer.WritePacket(packet);
        }
        return 0;
    }

    int EyerAVTranscode::InitEncoder(EyerAVWriter & writer)
    {
        int ret = 0;

        EyerAVReader reader(srcPath);
        reader.Open();
        int videoIndex = reader.GetVideoStreamIndex();
        if(videoIndex >= 0){
            // 初始化编码器
            if(params.careVideo){
                EyerAVEncoderParam videoEncoderParams;
                EyerAVRational encodeTimebase;
                encodeTimebase.num = 1;
                encodeTimebase.den = 1000;
                videoEncoderParams.InitH264(params.targetWidth, params.targetHeight, encodeTimebase);
                ret = videoEncoder.Init(videoEncoderParams);
                if(ret){
                    EyerLog("Video Encoder Init Fail\n");
                }
                encoderVideoStreamIndex = writer.AddStream(videoEncoder);
            }
        }

        int audioIndex = reader.GetAudioStreamIndex();
        if(audioIndex >= 0){
            // 初始化编码器
            if(params.careAudio) {
                EyerAVEncoderParam audioEncoderParams;
                audioEncoderParams.InitMP3(44100);
                ret = audioEncoder.Init(audioEncoderParams);
                if (ret) {
                    EyerLog("Audio Encoder Init Fail\n");
                }
                encoderAudioStreamIndex = writer.AddStream(audioEncoder);
            }
        }
        reader.Close();
        return 0;
    }
}