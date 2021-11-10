package com.zzsin.eyerplayer.jni;

public class EyerPlayerJNI {
    static {
        System.loadLibrary("EyerAndroidInterface");
    }

    public static native long   eyer_player_init        ();
    public static native int    eyer_player_uninit      (long eyer_player);

    public static native int    eyer_player_set_url     (long eyer_player, String url);
    public static native int    eyer_player_play        (long eyer_player);
    public static native int    eyer_player_pause       (long eyer_player);
    public static native int    eyer_player_resume      (long eyer_player);
}
