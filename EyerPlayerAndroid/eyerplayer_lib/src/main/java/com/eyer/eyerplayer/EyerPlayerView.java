package com.eyer.eyerplayer;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.eyer.eyerplayer.mediainfo.EyerMediaInfo;

public class EyerPlayerView extends SurfaceView implements SurfaceHolder.Callback {

    private EyerPlayer player = null;
    private int videoWidth = 0;
    private int videoHeight = 0;
    private EyerPlayerListener listener = null;

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

    public EyerPlayerView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        init();
    }

    private int init(){
        getHolder().addCallback(this);
        return 0;
    }

    private long glCtx = 0;
    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        player = new EyerPlayer();
        player.setListener(new MyEyerPlayerListener());

        Log.e("EyerPlayerView", "surfaceCreated");
        Surface surface = holder.getSurface();
        glCtx = EyerPlayerJNI.player_gl_ctx_create(surface, player.nativeId);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.e("EyerPlayerView", "surfaceChanged");
        EyerPlayerJNI.player_gl_ctx_set_wh(glCtx, width, height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        Log.e("EyerPlayerView", "surfaceDestroyed");
        EyerPlayerJNI.player_gl_ctx_destroyed(glCtx);

        if(player != null){
            player.destory();
        }
    }

    public int setListener(EyerPlayerListener listener){
        this.listener = listener;
        return 0;
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
