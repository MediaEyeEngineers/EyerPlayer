package com.eyer.eyerplayer;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.opengl.GLES11Ext;
import android.opengl.GLES20;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.eyer.eyerplayer.codec.EyerMediaCodec;

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


        // glContext = new EyerPlayerGLContext(holder.getSurface());


        int[] textures = new int[1];
        GLES20.glGenTextures(1, textures, 0);
        int mTextureID = textures[0];

        Log.e("GLDebug", "mTextureID: " + mTextureID);

        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, mTextureID);
        GLES20.glTexParameterf(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
        GLES20.glTexParameterf(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
        GLES20.glTexParameteri(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);

        SurfaceTexture mSurfaceTexture = new SurfaceTexture(mTextureID);
        Surface mDecoderSurface = new Surface(mSurfaceTexture);


        EyerMediaCodec.surface = holder.getSurface();

        if(this.listener != null){
            this.listener.afterCreated();
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        if(glContext != null){
            glContext.setWH(width, height);
        }
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
