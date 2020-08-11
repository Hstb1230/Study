package com.example.process_test;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.TextView;

import java.util.Locale;

public class MainActivity
        extends AppCompatActivity
{

    private SeekBar seekBar;
    private TextView textSeekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
        bindData();
        bindEvent();
    }

    private void bindData()
    {
        seekBar.setMax(180);
    }

    private void bindEvent()
    {
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(
                    SeekBar seekBar,
                    int progress,
                    boolean fromUser
            )
            {
                textSeekBar.setText(String.format(Locale.CHINA, "[%s] 当前进度：%d / %d", (fromUser ? "is User" : "no User"), progress, seekBar.getMax()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar)
            {
                System.out.println("onStartTrackingTouch: " + seekBar.isPressed());
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar)
            {

            }
        });
        new Thread()
        {
            @Override
            public void run()
            {
                super.run();

                while(true)
                {

                    System.out.println("isPressed: " + seekBar.isPressed());
                    if(!seekBar.isPressed())
                        seekBar.setProgress(seekBar.getProgress() + 1);

                    try
                    {
                        Thread.sleep(1000);
                    } catch(InterruptedException e)
                    {
                        e.printStackTrace();
                        break;
                    }

                }
            }
        }.start();
    }

    private void initView()
    {
        seekBar = (SeekBar) findViewById(R.id.seekBar);
        textSeekBar = (TextView) findViewById(R.id.textSeekBar);

    }
}
