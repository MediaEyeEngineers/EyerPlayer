package com.eyer.eyerplayer.gl;

import android.view.Surface;

import com.eyer.eyerplayer.EyerPlayerJNI;

public class EyerGLContext {

    private long nativeId = 0;

    public EyerGLContext(){
        nativeId = EyerPlayerJNI.gl_context_alloc();
    }

    public int destory(){
        if(nativeId != 0){
            EyerPlayerJNI.gl_context_dealloc(nativeId);
            nativeId = 0;
        }
        return 0;
    }

    public int init(Surface surface){
        return EyerPlayerJNI.gl_context_init(nativeId, surface);
    }

    public int uninit(){
        return EyerPlayerJNI.gl_context_uninit(nativeId);
    }

    public int makecurrent(){
        return EyerPlayerJNI.gl_context_makecurrent(nativeId);
    }

    public int startGLThread(){
        return EyerPlayerJNI.gl_context_start_gl_thread(nativeId);
    }

    public int stopGLThread(){
        return EyerPlayerJNI.gl_context_stop_gl_thread(nativeId);
    }
}
