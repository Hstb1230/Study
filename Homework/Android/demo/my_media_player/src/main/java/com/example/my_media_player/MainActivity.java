package com.example.my_media_player;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity
        extends AppCompatActivity
{

    private Button btnStart;
    private Button btnStop;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnStart = (Button) findViewById(R.id.button);
        btnStop = (Button) findViewById(R.id.button2);

        btnStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                startService(new Intent(getApplicationContext(), MusicService.class));
            }
        });
        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                stopService(new Intent(getApplicationContext(), MusicService.class));
            }
        });
    }
}
