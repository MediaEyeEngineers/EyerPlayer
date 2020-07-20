package com.eyer.eyerplayer;

public class EyerPlayerJNI {
    static {
        System.loadLibrary("EyerPlayerJNI");
    }

    public static native long       gl_context_init             ();
    public static native int        gl_context_change           (long ctx, int w, int h);
    public static native int        gl_context_uninit           (long ctx);
}
