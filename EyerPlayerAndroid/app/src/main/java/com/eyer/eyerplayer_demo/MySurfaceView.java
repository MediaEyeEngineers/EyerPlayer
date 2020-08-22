package com.eyer.eyerplayer_demo;

import android.content.Context;
import android.os.Environment;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import com.eyer.eyerplayer.EyerPlayer;
import com.eyer.eyerplayer.EyerPlayerListener;
import com.eyer.eyerplayer.mediainfo.EyerMediaInfo;

import java.io.File;

public class MySurfaceView extends SurfaceView implements SurfaceHolder.Callback{

    private SurfaceHolder mSurfaceHolder = null;
    private EyerPlayer player = null;

    int videoWidth = 0;
    int videoHeight = 0;

    public MySurfaceView(Context context) {
        super(context);
        init();
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public MySurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init() {
        mSurfaceHolder = getHolder();
        mSurfaceHolder.setKeepScreenOn(true);
        mSurfaceHolder.addCallback(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        player = new EyerPlayer();
        player.setListener(new MyEyerPlayerListener());
        player.setSurface(holder.getSurface());

        String videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/demo.mp4";
        videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/xinxiaomen.mp4";
        videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/bbb_sunflower_2160p_60fps_normal.mp4";
        videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/w.mp4";
        Log.e("MainActivity", videoPath);

        File videoFile = new File(videoPath);
        if(videoFile.exists()){
            Log.e("MainActivity", videoFile.canRead() + "");
        }

        // videoPath = "http://redknot.cn/sohu/hls/shuw.m3u8";
        player.open(videoPath);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.e("@@@@", "SurfaceChange， Width: " + width + " Height: " + height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        if(player != null){
            player.destory();
            player = null;
        }
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        int viewWidth = MeasureSpec.getSize(widthMeasureSpec);
        int viewHeight = MeasureSpec.getSize(heightMeasureSpec);
        // Log.e("@@@@", "onMeasure(" + MeasureSpec.getSize(widthMeasureSpec) + ", " + MeasureSpec.getSize(heightMeasureSpec) + ")");

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


    private class MyEyerPlayerListener implements EyerPlayerListener
    {
        @Override
        public int onOpen(EyerMediaInfo mediaInfo) {
            videoWidth = mediaInfo.getVideoStreamInfo().getWidth();
            videoHeight = mediaInfo.getVideoStreamInfo().getHeight();

            requestLayout();

            return 0;
        }
    }
}
