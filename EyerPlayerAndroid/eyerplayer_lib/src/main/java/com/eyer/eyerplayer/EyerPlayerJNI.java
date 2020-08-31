package com.eyer.eyerplayer;


public class EyerPlayerJNI {
    static {
        System.loadLibrary("EyerPlayerJNI");
    }

    public static native long       player_init                 ();
    public static native int        player_uninit               (long player);

    public static native int        player_set_surface          (long player, android.view.Surface surface);
    public static native int        player_set_callback         (long player, com.eyer.eyerplayer.callback.EyerCallback callback);

    public static native int        player_open                 (long player, String url);
    public static native int        player_play                 (long player);
    public static native int        player_pause                (long player);
    public static native int        player_stop                 (long player);
    public static native int        player_seek                 (long player, double time);



    public static native long       gl_context_alloc            ();
    public static native int        gl_context_dealloc          (long gl_context);

    public static native int        gl_context_init             (long gl_context, android.view.Surface surface);
    public static native int        gl_context_uninit           (long gl_context);

    public static native int        gl_context_makecurrent      (long gl_context);

    public static native int        gl_context_start_gl_thread  (long gl_context);
    public static native int        gl_context_stop_gl_thread   (long gl_context);

}
