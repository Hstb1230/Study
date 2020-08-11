package com.example.birthday;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;

public class MainActivity extends AppCompatActivity {

    private MediaPlayer player = null;
    private ImageView flag;
    private Handler handler;
    private int gap;
    private RelativeLayout background;

    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        flag = (ImageView)findViewById(R.id.flag);
        // getResources().getDisplayMetrics().heightPixels;
        background = (RelativeLayout)findViewById(R.id.background);

        handler = new Handler() {
            public void handleMessage(android.os.Message msg) {
                switch (msg.what) {
                    case 0:
                        // 移除所有的msg.what为0等消息，保证只有一个循环消息队列在运行
                        handler.removeMessages(0);
                        // app的功能逻辑处理
                        // ...
                        int loc = (int)((background.getMeasuredHeight() - flag.getMeasuredHeight()) * (1 - (1.0 * player.getCurrentPosition() / player.getDuration()))) + flag.getMeasuredHeight();
                        if(loc < flag.getMeasuredHeight())
                            break;
                        flag.setBottom(loc);
                        flag.setTop(loc - flag.getMeasuredHeight());
                        Log.v("bottom", String.valueOf(flag.getBottom()));
//                        RelativeLayout.MarginLayoutParams mlp = new RelativeLayout.MarginLayoutParams(flag.getWidth(), flag.getHeight());
//                        Log.v("width", String.valueOf(width));
//                        mlp.bottomMargin = (int)(width * (1.0 * player.getCurrentPosition() / player.getDuration()));
//                        RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(mlp);
//                        flag.setLayoutParams(lp);
                        // 再次发出msg，循环更新
                        handler.sendEmptyMessageDelayed(0, 50);
                        break;

                    case 1:
                        // 直接移除，定时器停止
//                        flag.setBottom(flag.getMeasuredHeight());
//                        flag.setTop(0);
                        handler.removeMessages(0);
                        break;

                    default:
                        break;
                }
            };
        };
    }

    public void stop(View view) {
        if(player == null)
            return;
        if(player.isPlaying())
        {
            handler.sendEmptyMessage(1);
            player.stop();
        }
        player.reset();
    }

    public void start(View view) {
        if(player == null || !player.isPlaying())
        {
            player = MediaPlayer.create(getApplicationContext(), R.raw.birthday);
        }
        else
        {
            return;
        }
        flag.setBottom(background.getMeasuredHeight() + flag.getMeasuredHeight());
        flag.setTop(background.getMeasuredHeight());
        flag.setVisibility(View.VISIBLE);
        handler.sendEmptyMessage(0);
        player.start();
        player.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mediaPlayer) {
                handler.sendEmptyMessage(1);
            }
        });
    }
}
