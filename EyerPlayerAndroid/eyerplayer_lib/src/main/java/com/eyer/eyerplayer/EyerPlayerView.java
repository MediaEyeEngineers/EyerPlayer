package com.eyer.eyerplayer;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class EyerPlayerView extends SurfaceView implements SurfaceHolder.Callback{

    public EyerPlayerView(Context context) {
        super(context);
        init();
    }

    public EyerPlayerView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public EyerPlayerView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init(){
        getHolder().addCallback(this);
    }



    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}
