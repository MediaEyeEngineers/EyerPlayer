package com.zzsin.eyerplayer.view;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceView;

import com.zzsin.eyerplayer.jni.EyerPlayerJNI;

public class EyerPlayerView extends SurfaceView {

    private long playerJNI = 0L;

    public EyerPlayerView(Context context) {
        super(context);
        init();
    }

    public EyerPlayerView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public EyerPlayerView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private int init() {
        playerJNI = EyerPlayerJNI.eyer_player_init();
        return 0;
    }

    public int destory() {
        if(playerJNI != 0L){
            EyerPlayerJNI.eyer_player_uninit(playerJNI);
            playerJNI = 0L;
        }
        return 0;
    }

    public int setUrl(String url){
        return EyerPlayerJNI.eyer_player_set_url(playerJNI, url);
    }

    public int play(){
        return EyerPlayerJNI.eyer_player_play(playerJNI);
    }

    public int stop(){
        return EyerPlayerJNI.eyer_player_stop(playerJNI);
    }
}
