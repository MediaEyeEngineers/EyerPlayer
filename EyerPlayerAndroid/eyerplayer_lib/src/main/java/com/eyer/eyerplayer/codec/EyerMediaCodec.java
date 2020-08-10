package com.eyer.eyerplayer.codec;

import android.media.MediaCodec;
import android.media.MediaFormat;
import android.view.Surface;

import java.io.IOException;

public class EyerMediaCodec {
    public int init(Surface surface){
        MediaCodec mediaCodec = null;
        try {
            mediaCodec = MediaCodec.createDecoderByType(MediaFormat.MIMETYPE_VIDEO_AVC);
        } catch (IOException e) {
            e.printStackTrace();
        }

        int width = 1080;
        int height = 1920;

        MediaFormat mediaFormat = MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_AVC, width, height);
        mediaCodec.configure(mediaFormat, surface, null, 0);
        mediaCodec.start();

        mediaCodec.setVideoScalingMode(MediaCodec.VIDEO_SCALING_MODE_SCALE_TO_FIT_WITH_CROPPING);

        return 0;
    }
}
