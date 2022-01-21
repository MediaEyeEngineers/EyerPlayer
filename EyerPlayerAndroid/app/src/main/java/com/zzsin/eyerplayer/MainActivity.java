package com.zzsin.eyerplayer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.zzsin.eyerplayer.view.EyerPlayerView;
import com.zzsin.eyerplayer.view.EyerPlayerViewListener;

public class MainActivity extends AppCompatActivity {

    private EyerPlayerView playerView = null;

    private Button btn_play = null;
    private Button btn_stop = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn_play = findViewById(R.id.btn_play);
        btn_stop = findViewById(R.id.btn_stop);

        btn_play.setOnClickListener(new MyClickListener());
        btn_stop.setOnClickListener(new MyClickListener());

        playerView = findViewById(R.id.eyer_player_view);
        playerView.initPlayer(new MyEyerPlayerViewListener());
    }

    private class MyClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            if(view == btn_play){
                playerView.setUrl("");
                playerView.play();
            }
            else if(view == btn_stop){
                playerView.stop();
            }
        }
    }

    private class MyEyerPlayerViewListener implements EyerPlayerViewListener {
        @Override
        public void onPlayerCreate() {
            playerView.setUrl("");
            playerView.play();
        }
    }
}