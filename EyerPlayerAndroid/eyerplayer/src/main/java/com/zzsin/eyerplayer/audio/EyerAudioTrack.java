package com.zzsin.eyerplayer.audio;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;

public class EyerAudioTrack {

    private AudioTrack audioTrack = null;

    public EyerAudioTrack(int sampleRate) {
        int bufferSize = AudioTrack.getMinBufferSize(
                sampleRate,
                AudioFormat.CHANNEL_OUT_MONO,
                AudioFormat.ENCODING_PCM_16BIT );

        audioTrack = new AudioTrack (
                AudioManager.STREAM_MUSIC,
                sampleRate,
                AudioFormat.CHANNEL_OUT_MONO,
                AudioFormat.ENCODING_PCM_16BIT,
                bufferSize,
                AudioTrack.MODE_STREAM );
    }

    public int write(byte[] buffer) {
        int len = buffer.length;
        return audioTrack.write(buffer, 0, len);
    }

    public void play() {
        audioTrack.play();
    }

    public void stop() {
        audioTrack.stop();
    }
}
