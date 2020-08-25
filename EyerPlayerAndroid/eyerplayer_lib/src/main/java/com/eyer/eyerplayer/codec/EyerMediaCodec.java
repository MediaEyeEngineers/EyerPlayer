package com.eyer.eyerplayer.codec;

import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.media.MediaFormat;
import android.util.Log;
import android.view.Surface;

import java.io.IOException;
import java.nio.ByteBuffer;

public class EyerMediaCodec {

    private MediaCodec mediaCodec = null;

    private MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();

    public int init(int width, int height, Surface surface){
        displayDecoders();
        Log.e("EyerMediaCodec", "width: " + width + " height: " + height);

        try {
            mediaCodec = MediaCodec.createDecoderByType(MediaFormat.MIMETYPE_VIDEO_AVC);
        } catch (IOException e) {
            e.printStackTrace();
        }

        MediaFormat mediaFormat = MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_AVC, width, height);
        mediaCodec.configure(mediaFormat, surface, null, 0);
        mediaCodec.start();

        return 0;
    }

    public int uninit(){
        if(mediaCodec == null){
            return -1;
        }

        mediaCodec.stop();
        mediaCodec.release();

        return 0;
    }


    /// Input
    public int dequeueInputBuffer(long timeoutUs){
        return mediaCodec.dequeueInputBuffer(timeoutUs);
    }
    public int putInputData(int index, byte[] data){
        ByteBuffer inputBuf = mediaCodec.getInputBuffers()[index];
        inputBuf.clear();
        inputBuf.put(data);

        return 0;
    }

    public void queueInputBuffer(int index, int offset, int size, long presentationTimeUs, int flags) {
        mediaCodec.queueInputBuffer(index, offset, size, presentationTimeUs, flags);
    }



    /// Output
    public int dequeueOutputBuffer(long timeoutUs) {
        int outindex = mediaCodec.dequeueOutputBuffer(bufferInfo, timeoutUs);
        return outindex;
    }

    public long getOutTime(){
        return bufferInfo.presentationTimeUs;
    }

    public int releaseOutputBuffer(int index, boolean render){
        ByteBuffer outputBuffer = mediaCodec.getOutputBuffers()[index];
        mediaCodec.releaseOutputBuffer(index, render);

        return 0;
    }











    public int send(byte[] data, long time){
        int inputBufIndex = mediaCodec.dequeueInputBuffer(1000);

        if (inputBufIndex >= 0) {
            ByteBuffer inputBuf = mediaCodec.getInputBuffers()[inputBufIndex];
            inputBuf.clear();
            inputBuf.put(data);

            mediaCodec.queueInputBuffer(inputBufIndex, 0, data.length, time, 0);

            return 0;
        }

        return -1;
    }

    public int recvAndRender(){
        MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
        int outindex = mediaCodec.dequeueOutputBuffer(bufferInfo, 1000);

        if (outindex >= 0) {
            ByteBuffer outputBuffer = mediaCodec.getOutputBuffers()[outindex];
            mediaCodec.releaseOutputBuffer(outindex, true);
            return 0;
        }

        return -1;
    }










    private void displayDecoders() {
        MediaCodecList list = null;
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
            list = new MediaCodecList(MediaCodecList.REGULAR_CODECS);
        }
        MediaCodecInfo[] codecs = new MediaCodecInfo[0];
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
            codecs = list.getCodecInfos();
        }
        if(list != null) {
            for (MediaCodecInfo codec : codecs) {
                if (codec.isEncoder())
                    continue;
                Log.e("EyerMediaCodec", "Decoder Name: " + codec.getName());
            }
        }
    }
}