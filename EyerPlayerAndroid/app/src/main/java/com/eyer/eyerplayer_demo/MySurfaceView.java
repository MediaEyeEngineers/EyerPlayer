package com.eyer.eyerplayer_demo;

import android.content.Context;
import android.os.Environment;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.eyer.eyerplayer.EyerPlayer;

import java.io.File;

public class MySurfaceView extends SurfaceView implements SurfaceHolder.Callback{

    private SurfaceHolder mSurfaceHolder = null;

    private EyerPlayer player = null;

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
        mSurfaceHolder.addCallback(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        player = new EyerPlayer();
        player.SetSurface(holder.getSurface());

        String videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/demo.mp4";
        videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/xinxiaomen.mp4";
        // videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/bbb_sunflower_2160p_60fps_normal.mp4";
        Log.e("MainActivity", videoPath);

        File videoFile = new File(videoPath);
        if(videoFile.exists()){
            Log.e("MainActivity", videoFile.canRead() + "");
        }

        // videoPath = "http://redknot.cn/sohu/hls/shuw.m3u8";
        player.Open(videoPath);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        if(player != null){
            player.destory();
            player = null;
        }
    }
}
