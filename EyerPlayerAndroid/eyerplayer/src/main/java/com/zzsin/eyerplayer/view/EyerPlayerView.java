package com.zzsin.eyerplayer.view;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceView;

import com.zzsin.eyerplayer.jni.EyerPlayerJNI;

public class EyerPlayerView extends SurfaceView {
    public EyerPlayerView(Context context) {
        super(context);
    }

    public EyerPlayerView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public EyerPlayerView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public int play() {
        EyerPlayerJNI.eyer_player_init();
        return 0;
    }

    public int stop()  {
        return 0;
    }
}
