package com.zzsin.eyerplayer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import com.zzsin.eyerplayer.view.EyerPlayerView;
import com.zzsin.eyerplayer.view.EyerPlayerViewListener;

public class MainActivity extends AppCompatActivity {

    private EyerPlayerView playerView = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        playerView = findViewById(R.id.eyer_player_view);
        playerView.initPlayer(new MyEyerPlayerViewListener());
    }

    private class MyEyerPlayerViewListener implements EyerPlayerViewListener
    {
        @Override
        public int afterCreated() {
            Log.e("Eyer Player", "MyEyerPlayerViewListener afterCreated");
            playerView.setUrl("");
            playerView.play();
            return 0;
        }

        @Override
        public int beforeDestory() {
            Log.e("Eyer Player", "MyEyerPlayerViewListener beforeDestory");
            playerView.stop();
            return 0;
        }
    }
}