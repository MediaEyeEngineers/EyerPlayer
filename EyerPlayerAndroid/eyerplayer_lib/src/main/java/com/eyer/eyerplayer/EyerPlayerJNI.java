package com.eyer.eyerplayer;

import android.view.Surface;

public class EyerPlayerJNI {
    static {
        System.loadLibrary("EyerPlayerJNI");
    }

    public static native long       player_init                 ();
    public static native int        player_uninit               (long player);
    public static native int        player_setsurface           (long player, Surface surface);
    public static native int        player_open                 (long player, String url);
}
