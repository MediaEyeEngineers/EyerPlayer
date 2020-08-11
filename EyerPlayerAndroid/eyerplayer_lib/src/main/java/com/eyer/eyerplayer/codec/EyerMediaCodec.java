package com.eyer.eyerplayer.codec;

import android.media.MediaCodec;
import android.media.MediaFormat;
import android.util.Log;
import android.view.Surface;

import java.io.IOException;
import java.nio.ByteBuffer;

public class EyerMediaCodec {

    private MediaCodec mediaCodec = null;

    public int init(int width, int height){
        Log.e("EyerMediaCodec", "width: " + width + " height: " + height);

        try {
            mediaCodec = MediaCodec.createDecoderByType(MediaFormat.MIMETYPE_VIDEO_AVC);
        } catch (IOException e) {
            e.printStackTrace();
        }

        MediaFormat mediaFormat = MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_AVC, width, height);
        mediaCodec.configure(mediaFormat, null, null, 0);
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

    public int input(){
        int inputBufIndex = mediaCodec.dequeueInputBuffer(10000);
        if (inputBufIndex >= 0) {
            ByteBuffer inputBuf = mediaCodec.getInputBuffers()[inputBufIndex];
            mediaCodec.queueInputBuffer(inputBufIndex, 0, chunkSize, mMediaExtractor.getSampleTime(), 0);
        }

        return 0;
    }
}
