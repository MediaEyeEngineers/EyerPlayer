package com.eyer.eyerplayer;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class EyerPlayerView extends SurfaceView implements SurfaceHolder.Callback{

    private EyerPlayerViewListener listener;

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

    public int setListener(EyerPlayerViewListener listener){
        this.listener = listener;
        return 0;
    }

    private void init(){
        getHolder().addCallback(this);
    }

    private EyerPlayerGLContext glContext = null;

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        if(this.listener != null){
            this.listener.beforeCreated();
        }

        if(glContext != null){
            glContext.destory();
            glContext = null;
        }

        glContext = new EyerPlayerGLContext(holder.getSurface());

        if(this.listener != null){
            this.listener.afterCreated();
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        glContext.setWH(width, height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        if(this.listener != null){
            this.listener.beforeDestroyed();
        }

        if(glContext != null){
            glContext.destory();
            glContext = null;
        }

        if(this.listener != null){
            this.listener.afterDestroyed();
        }
    }

    public EyerPlayerGLContext getGLCtx(){
        return this.glContext;
    }
}
