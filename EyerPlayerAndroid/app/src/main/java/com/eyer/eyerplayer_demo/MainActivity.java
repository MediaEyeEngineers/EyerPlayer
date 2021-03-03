package com.eyer.eyerplayer_demo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.TextView;

import com.eyer.eyerplayer.EyerPlayer;
import com.eyer.eyerplayer.EyerPlayerListener;
import com.eyer.eyerplayer.EyerPlayerView;
import com.eyer.eyerplayer.mediainfo.EyerMediaInfo;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private static String[] PERMISSIONS_STORAGE = {
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.WRITE_EXTERNAL_STORAGE" };
    private static final int REQUEST_EXTERNAL_STORAGE = 1;

    // private EyerPlayer player = null;
    private Button btn_open = null;
    private Button btn_stop = null;
    private Button btn_play = null;
    private Button btn_pause = null;

    private TextView log_textview = null;

    private SeekBar progress_seek_bar = null;

    private EyerPlayerView video_view = null;

    private boolean isSeeking = false;


    private EyerMediaInfo mediaInfo = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        verifyStoragePermissions(this);

        video_view = findViewById(R.id.video_view);
        video_view.setListener(new MyEyerPlayerListener());

        btn_open = findViewById(R.id.btn_open);
        btn_stop = findViewById(R.id.btn_stop);
        btn_pause = findViewById(R.id.btn_pause);
        btn_play = findViewById(R.id.btn_play);
        log_textview = findViewById(R.id.log_textview);

        progress_seek_bar = findViewById(R.id.progress_seek_bar);
        progress_seek_bar.setMax(100);

        btn_open.setOnClickListener(new MyClickListener());
        btn_play.setOnClickListener(new MyClickListener());
        btn_pause.setOnClickListener(new MyClickListener());
        btn_stop.setOnClickListener(new MyClickListener());

        progress_seek_bar.setOnTouchListener(new MySeekBarOnTouchListener());
    }



    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    protected void onRestart() {
        super.onRestart();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    private static void verifyStoragePermissions(Activity activity) {
        try {
            int permission = ActivityCompat.checkSelfPermission(activity, PERMISSIONS_STORAGE[0]);
            if (permission != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(activity, PERMISSIONS_STORAGE, REQUEST_EXTERNAL_STORAGE);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private class MyEyerPlayerListener implements EyerPlayerListener {
        @Override
        public int onOpen(int status, EyerMediaInfo _mediaInfo) {
            String log = "open video ";
            if(status == EyerPlayerListener.OPEN_STATUS_SUCCESS){
                log += "success.";
                mediaInfo = _mediaInfo;
            }
            if(status == EyerPlayerListener.OPEN_STATUS_FAIL){
                log += "fail.";
            }
            if(status == EyerPlayerListener.OPEN_STATUS_BUSY){
                log += "busy, stop first.";
            }
            log_textview.setText(log);
            return 0;
        }

        @Override
        public int onProgress(double progress) {
            if(!isSeeking){
                progress_seek_bar.setProgress((int)(100 * progress));
            }
            return 0;
        }
    }

    private class MyClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            if(view == btn_open){
                String videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/demo.mp4";
                videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/demo/demo1.mp4";
                // videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/xinxiaomen.mp4";
                // videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/size_merge.mp4";
                // videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/bbb_sunflower_2160p_60fps_normal.mp4";
                // videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/w.mp4";
                // videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/demo.mp4";
                // videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/bbb_1080p.mp4";

                Log.e("MainActivity", videoPath);

                File videoFile = new File(videoPath);

                if(videoFile.exists()){
                    Log.e("MainActivity", videoFile.canRead() + "");
                }

                // videoPath = "http://redknot.cn/sohu/hls/shuw.m3u8";
                // videoPath = "https://dash.akamaized.net/akamai/bbb_30fps/bbb_30fps.mpd";

                video_view.open(videoPath);
            }
            if(view == btn_play){
                video_view.play();
            }
            if(view == btn_pause){
                video_view.pause();
            }
            if(view == btn_stop){
                video_view.stop();
            }
        }
    }

    private class MySeekBarOnTouchListener implements View.OnTouchListener {
        @Override
        public boolean onTouch(View view, MotionEvent motionEvent) {
            if(motionEvent.getAction() == MotionEvent.ACTION_DOWN){
                isSeeking = true;
            }
            if(motionEvent.getAction() == MotionEvent.ACTION_UP){
                isSeeking = false;
                SeekBar seekBar = (SeekBar)view;
                int progress = seekBar.getProgress();
                Log.e("SeekBar", "progress: " + progress);

                if(mediaInfo != null){
                    double duration = mediaInfo.getDuration();
                    // video_view.seek(progress / 100.0 * 1000.0);
                    video_view.seek(progress / 100.0 * duration);
                }
            }
            return false;
        }
    }
}
