package com.eyer.eyerplayer;

public class EyerPlayerGLContext {
    private long nativeId = 0;

    public EyerPlayerGLContext(){
        nativeId = EyerPlayerJNI.gl_context_init();
    }

    public int setWH(int w, int h){
        return EyerPlayerJNI.gl_context_change(nativeId, w, h);
    }

    public int destory(){
        if(nativeId != 0){
            EyerPlayerJNI.gl_context_uninit(nativeId);
            nativeId = 0;
        }
        return 0;
    }
}
