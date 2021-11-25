package com.zzsin.eyerplayer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.zzsin.eyerplayer.view.EyerPlayerView;

public class MainActivity extends AppCompatActivity {

    private EyerPlayerView playerView = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        playerView = findViewById(R.id.eyer_player_view);
        playerView.setUrl("https://www.zzsin.com/hdr/V/ysjf.m3u8");
        playerView.play();
    }

    @Override
    protected void onStop() {
        super.onStop();
        if(playerView != null){
            playerView.stop();
            playerView.destory();
            playerView = null;
        }
    }
}