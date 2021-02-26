package com.eyer.eyerplayer;

import android.view.Surface;

import com.eyer.eyerplayer.callback.EyerCallback;

public class EyerPlayer {

    protected long nativeId = 0;

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
        return EyerPlayerJNI.player_stop(nativeId);
    }

    public int play(){
        return EyerPlayerJNI.player_play(nativeId);
    }

    public int pause() {
        return EyerPlayerJNI.player_pause(nativeId);
    }

    public int seek(double time){
        return EyerPlayerJNI.player_seek(nativeId, time);
    }

    public int switchRepresentation(int representationId) {
        return EyerPlayerJNI.switch_representation(nativeId, representationId);
    }

    public int renderInit() {
        return EyerPlayerJNI.player_render_init(nativeId);
    }

    public int renderUninit() {
        return EyerPlayerJNI.player_render_uninit(nativeId);
    }

    public int renderDraw(int texId) {
        return EyerPlayerJNI.player_render_draw(nativeId, texId);
    }
}
