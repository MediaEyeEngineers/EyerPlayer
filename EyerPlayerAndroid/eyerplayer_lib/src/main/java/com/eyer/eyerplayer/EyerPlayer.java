package com.eyer.eyerplayer;

import android.view.Surface;

import com.eyer.eyerplayer.callback.EyerCallback;

public class EyerPlayer {

    private long nativeId = 0;

    public EyerPlayer(){
        nativeId = EyerPlayerJNI.player_init();
    }

    public void destory(){
        if(nativeId != 0){
            EyerPlayerJNI.player_uninit(nativeId);
            nativeId = 0;
        }
    }

    public int setListener(EyerPlayerListener listener) {
        EyerCallback callback = new EyerCallback(listener);
        EyerPlayerJNI.player_set_callback(nativeId, callback);
        return 0;
    }

    public int setSurface(Surface surface){
        return EyerPlayerJNI.player_set_surface(nativeId, surface);
    }

    public int open(String url){
        return EyerPlayerJNI.player_open(nativeId, url);
    }

    public int stop(){
        return 0;
    }

    public int play(){
        return 0;
    }

    public int pause() {
        return 0;
    }
}
