package com.example.frame_animation;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.TextView;

import java.util.Arrays;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    private int currentColor = 0;
    final int[] colorArrayInR = new int[] {
            R.color.color1,
            R.color.color2,
            R.color.color3,
            R.color.color4,
            R.color.color5,
            R.color.color6
    };
    // 不能在初始化时候赋值资源值, 否则会闪退
    int[] colorArray;
    final int[] textViewArray = new int[] {
            R.id.textView,
            R.id.textView2,
            R.id.textView3,
            R.id.textView4,
            R.id.textView5,
            R.id.textView6
    };
    TextView[] views;

    @SuppressLint("HandlerLeak")
    Handler handler = new Handler() {
        @Override
        public void handleMessage(Message message) {
            // 表示消息由本程序发送
            if(message.what == 0x123) {
                for(int i = 0; i < views.length; i++) {
                    // 不能用setBackgroundColor
//                    views[i].setBackgroundResource(colors[(i + currentColor) % colors.length]);
                    views[i].setBackgroundColor(colorArray[(i + currentColor) % colorArray.length]);
                }
                currentColor++;
            }
            super.handleMessage(message);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        colorArray = getResources().getIntArray(R.array.colorArray);
        Log.v("colorArray", Arrays.toString(colorArray));
        Log.v("colorArrayInR", Arrays.toString(colorArrayInR));
        Log.v("textViewArray", Arrays.toString(textViewArray));
        views = new TextView[textViewArray.length];
        for(int i = 0; i < textViewArray.length; i++) {
            views[i] = findViewById(textViewArray[i]);
        }


        // 定义一个线程, 周期性的改变颜色
        // 两种方法
//        new Timer().schedule(new TimerTask() {
//            @Override
//            public void run() {
//                handler.sendEmptyMessage(0x123);
//            }
//        }, 0, 200);

        Timer timer = new Timer();
        TimerTask timerTask = new TimerTask() {
            @Override
            public void run()
            {
                handler.sendEmptyMessage(0x123);
            }
        };
        timer.schedule(timerTask, 0, 200);
    }
}
