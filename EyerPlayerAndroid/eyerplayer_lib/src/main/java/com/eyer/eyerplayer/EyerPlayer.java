package com.eyer.eyerplayer;

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

    public int Open(String url){
        return 0;
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
