package com.eyer.eyerplayer_demo;

import android.content.Context;
import android.graphics.SurfaceTexture;

import android.opengl.GLES11Ext;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;

import com.eyer.eyerplayer.EyerPlayer;
import com.eyer.eyerplayer.EyerPlayerListener;
import com.eyer.eyerplayer.mediainfo.EyerMediaInfo;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MySurfaceView extends GLSurfaceView implements GLSurfaceView.Renderer, SurfaceTexture.OnFrameAvailableListener{

    private EyerPlayer player = null;

    int videoWidth = 0;
    int videoHeight = 0;

    private EyerPlayerListener listener = null;

    private int textureId_mediacodec = -1;

    private boolean android_mediacodec = true;

    public MySurfaceView(Context context) {
        super(context);
        init();
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        setEGLContextClientVersion(3);
        setRenderer(this);
        // setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
        setKeepScreenOn(true);

        player = new EyerPlayer();
        player.setListener(new MyEyerPlayerListener());
    }

    public int setListener(EyerPlayerListener listener){
        this.listener = listener;
        return 0;
    }

    public int switchRepresentation(int representationId){
        return player.switchRepresentation(representationId);
    }

    public int open(String url){
        return player.open(url);
    }

    public int play(){
        return player.play();
    }

    public int pause(){
        return player.pause();
    }

    public int stop(){
        return player.stop();
    }

    public int seek(double time) {
        return player.seek(time);
    }


    private SurfaceTexture surfaceTexture = null;
    private Surface surface = null;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // 控件创建把Opengl初始化

        //T Log.e("Eyer OpenGL", "onSurfaceCreated");

        player.renderInit();

        int[] textureids = new int[1];
        GLES20.glGenTextures(1, textureids, 0);
        textureId_mediacodec = textureids[0];

        GLES20.glTexParameteri(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_REPEAT);
        GLES20.glTexParameteri(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_REPEAT);
        GLES20.glTexParameteri(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);

        //T Log.e("Eyer OpenGL", "textureId_mediacodec: " + textureId_mediacodec);


        surfaceTexture = new SurfaceTexture(textureId_mediacodec);

        surface = new Surface(surfaceTexture);

        surfaceTexture.setOnFrameAvailableListener(this);

        player.setSurface(surface);
    }



    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        //T Log.e("Eyer OpenGL", "onSurfaceChanged");
        GLES20.glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        // Log.e("Eyer OpenGL", "onDrawFrame");
        surfaceTexture.updateTexImage();
        // EyerPlayerJNI.player_gl_draw(textureId_mediacodec);

        player.renderDraw(textureId_mediacodec);
    }


    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {
        long time = surfaceTexture.getTimestamp();
        requestRender();
        // Log.e("MyEyerPlayerListener", "onFrameAvailable======" + time);
    }


    private class MyEyerPlayerListener implements EyerPlayerListener
    {
        @Override
        public int onOpen(int status, EyerMediaInfo mediaInfo) {
            // Log.e("MyEyerPlayerListener", "onOpen");
            if(status == EyerPlayerListener.OPEN_STATUS_SUCCESS){
                videoWidth = mediaInfo.getVideoStreamInfo().getWidth();
                videoHeight = mediaInfo.getVideoStreamInfo().getHeight();
                requestLayout();
            }

            if(listener != null){
                listener.onOpen(status, mediaInfo);
            }
            return 0;
        }

        @Override
        public int onProgress(double process) {
            if(listener != null){
                listener.onProgress(process);
            }
            return 0;
        }
    }


    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        int viewWidth = MeasureSpec.getSize(widthMeasureSpec);
        int viewHeight = MeasureSpec.getSize(heightMeasureSpec);

        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

        if(videoWidth > 0 && videoHeight >0){
            int mWidth = 0;
            int mHeight = 0;

            float fitView = (float)(viewWidth * 1.0 / viewHeight);
            float fitVideo = (float)(videoWidth * 1.0 / videoHeight);

            if(fitView > fitVideo){
                mHeight = viewHeight;
                mWidth = (int)(videoWidth * 1.0 / videoHeight * mHeight);
            }
            else{
                mWidth = viewWidth;
                mHeight = (int)(videoHeight * 1.0 / videoWidth * mWidth);
            }

            setMeasuredDimension(mWidth, mHeight);
        }
    }
}
