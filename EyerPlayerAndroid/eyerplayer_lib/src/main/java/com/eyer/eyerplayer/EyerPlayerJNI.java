package com.eyer.eyerplayer;

import android.view.Surface;

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
    public static native int        switch_representation       (long player, int representation);


    public static native long       player_gl_ctx_create        (Surface surface, long player);
    public static native int        player_gl_ctx_set_wh        (long gl_ctx, int w, int h);
    public static native int        player_gl_ctx_destroyed     (long gl_ctx);


    public static native int        player_render_init          (long player);
    public static native int        player_render_draw          (long player, int texId);
    public static native int        player_render_uninit        (long player);

    public static native int        player_gl_init              ();
    public static native int        player_gl_draw              (int texId);
    public static native int        player_gl_viewport          (int w, int h);
}
