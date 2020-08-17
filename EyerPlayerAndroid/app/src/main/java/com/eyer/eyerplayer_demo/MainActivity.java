package com.eyer.eyerplayer_demo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.Paint;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;

import com.eyer.eyerplayer.EyerPlayer;
import com.eyer.eyerplayer.EyerPlayerView;
import com.eyer.eyerplayer.EyerPlayerViewListener;
import com.eyer.eyerplayer.codec.EyerMediaCodec;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private static String[] PERMISSIONS_STORAGE = {
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.WRITE_EXTERNAL_STORAGE" };
    private static final int REQUEST_EXTERNAL_STORAGE = 1;

    private EyerPlayerView eyer_player_view = null;
    private EyerPlayer player = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        verifyStoragePermissions(this);

        player = new EyerPlayer();

        eyer_player_view = findViewById(R.id.eyer_player_view);
        eyer_player_view.setListener(new MyEyerPlayerViewListener());
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
        if(player != null){
            player.destory();
            player = null;
        }
    }

    private class MyEyerPlayerViewListener implements EyerPlayerViewListener {

        @Override
        public int beforeCreated() {
            Log.e("Listener", "beforeCreated");
            return 0;
        }

        @Override
        public int afterCreated() {
            Log.e("Listener", "afterCreated");
            // player.SetPlayerView(eyer_player_view);

            String videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/demo.mp4";
            videoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ST/xinxiaomen.mp4";
            Log.e("MainActivity", videoPath);

            File videoFile = new File(videoPath);
            if(videoFile.exists()){
                Log.e("MainActivity", videoFile.canRead() + "");
            }

            // videoPath = "http://redknot.cn/sohu/hls/shuw.m3u8";
            player.Open(videoPath);

            return 0;
        }

        @Override
        public int beforeDestroyed() {
            Log.e("Listener", "beforeDestroyed");
            player.UnsetPlayerView();
            return 0;
        }

        @Override
        public int afterDestroyed() {
            Log.e("Listener", "afterDestroyed");
            return 0;
        }
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
}
