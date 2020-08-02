package com.eyer.eyerplayer;

public class EyerPlayer {

    private long nativeId = 0;

    public EyerPlayer(){
        nativeId = EyerPlayerJNI.player_init();
    }

    private int SetGLCtx(EyerPlayerGLContext glCtx){
        return EyerPlayerJNI.player_set_gl_ctx(nativeId, glCtx.getNativeId());
    }
    private int UnsetGLCtx(){
        return EyerPlayerJNI.player_unset_gl_ctx(nativeId);
    }

    public int SetPlayerView(EyerPlayerView playerView){
        return SetGLCtx(playerView.getGLCtx());
    }

    public int UnsetPlayerView(){
        return UnsetGLCtx();
    }

    public void destory(){
        if(nativeId != 0){
            EyerPlayerJNI.player_uninit(nativeId);
            nativeId = 0;
        }
    }

    public int Open(String url){
        return EyerPlayerJNI.player_open(nativeId, url);
    }

    public int Close(){
        return 0;
    }

    public int Play(){
        return 0;
    }

    public int Pause() {
        return 0;
    }
}
