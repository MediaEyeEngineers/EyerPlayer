package com.zzsin.eyerplayer.view;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

import com.zzsin.eyerplayer.jni.EyerPlayerJNI;

public class EyerPlayerView extends SurfaceView implements SurfaceHolder.Callback {

    private long playerJNI = 0L;
    private EyerPlayerViewListener listener = null;
    private Context context = null;

    public EyerPlayerView(Context context) {
        super(context);
        init(context);
    }

    public EyerPlayerView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public EyerPlayerView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private int init(Context context) {
        setKeepScreenOn(true);
        this.context = context;
        return 0;
    }

    public int initPlayer(EyerPlayerViewListener listener){
        this.listener = listener;
        getHolder().addCallback(this);
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

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder surfaceHolder) {
        playerJNI = EyerPlayerJNI.eyer_player_init();

        if(this.listener != null){
            this.listener.onPlayerCreate();
        }
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder surfaceHolder, int i, int i1, int i2) {

    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder surfaceHolder) {
        if(playerJNI != 0L){
            EyerPlayerJNI.eyer_player_uninit(playerJNI);
            playerJNI = 0L;
        }
    }
}
