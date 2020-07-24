package com.eyer.eyerplayer_demo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.eyer.eyerplayer.EyerPlayer;

public class MainActivity extends AppCompatActivity {

    private EyerPlayer player = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        player = new EyerPlayer();
        player.Open("/a/a/a.mp4");
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
}
