package com.eyer.eyerplayer_demo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.eyer.eyerplayer.EyerPlayer;

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

    private MySurfaceView video_view = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        verifyStoragePermissions(this);

        video_view = findViewById(R.id.video_view);

        btn_open = findViewById(R.id.btn_open);
        btn_stop = findViewById(R.id.btn_stop);
        btn_pause = findViewById(R.id.btn_pause);
        btn_play = findViewById(R.id.btn_play);

        btn_open.setOnClickListener(new MyClickListener());
        btn_play.setOnClickListener(new MyClickListener());
        btn_pause.setOnClickListener(new MyClickListener());
        btn_stop.setOnClickListener(new MyClickListener());
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

    private class MyClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            if(view == btn_open){
                String videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/demo.mp4";
                videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/xinxiaomen.mp4";
                videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/bbb_sunflower_2160p_60fps_normal.mp4";
                videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/w.mp4";
                videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/demo.mp4";
                Log.e("MainActivity", videoPath);

                File videoFile = new File(videoPath);
                if(videoFile.exists()){
                    Log.e("MainActivity", videoFile.canRead() + "");
                }

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
}
