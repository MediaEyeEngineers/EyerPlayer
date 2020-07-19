package com.eyer.eyerplayer_demo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.eyer.eyerplayer.EyerPlayer;

public class MainActivity extends AppCompatActivity {

    private EyerPlayer player;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        player = new EyerPlayer();
        player.Open("");
    }
}
