package com.eyer.eyerplayer.codec;

import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.media.MediaFormat;
import android.os.Build;
import android.util.Log;
import android.view.Surface;

import androidx.annotation.RequiresApi;

import java.io.IOException;
import java.nio.ByteBuffer;

public class EyerMediaCodec {

    private MediaCodec mediaCodec = null;
    public static Surface surface = null;

    public int init(int width, int height){
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

    private void displayDecoders() {
        MediaCodecList list = null;//REGULAR_CODECS参考api说明
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

    public int send(byte[] data){
        // 返回输入缓冲区的索引
        int inputBufIndex = mediaCodec.dequeueInputBuffer(-1);
        Log.e("MediaCodec", "dequeueInputBuffer: " + inputBufIndex);

        // Log.e("MediaCodec", " " + data[0] + " " + data[1] + " " + data[2] + " " + data[3] + " " + data[4]);
        // Log.e("MediaCodec", "nalu type: " + (data[4] & 0x1F));


        if (inputBufIndex >= 0) {
            // 获取索引成功
            ByteBuffer inputBuf = mediaCodec.getInputBuffers()[inputBufIndex];
            inputBuf.clear();
            inputBuf.put(data);

            mediaCodec.queueInputBuffer(inputBufIndex, 0, data.length, 0, 0);
        }

        return 0;
    }

    public int recvAndRender(){
        MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
        int outindex = mediaCodec.dequeueOutputBuffer(bufferInfo, 1);
        if (outindex >= 0) {
            ByteBuffer outputBuffer = mediaCodec.getOutputBuffers()[outindex];
            mediaCodec.releaseOutputBuffer(outindex, true);

            return 0;
        }
        return -1;
    }
}