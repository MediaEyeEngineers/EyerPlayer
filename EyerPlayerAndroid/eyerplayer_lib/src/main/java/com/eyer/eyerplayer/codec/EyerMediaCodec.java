package com.eyer.eyerplayer.codec;

import android.media.MediaCodec;
import android.media.MediaFormat;
import android.util.Log;
import android.view.Surface;

import java.io.IOException;

public class EyerMediaCodec {

    /*
    public int init(int width, int height, Surface surface){
        MediaCodec mediaCodec = null;
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
    */

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
}
