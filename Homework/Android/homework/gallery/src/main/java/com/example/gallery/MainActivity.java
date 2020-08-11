package com.example.gallery;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import pl.droidsonroids.gif.GifDrawable;
import pl.droidsonroids.gif.GifImageView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private List<Integer> images;
    private Button lastBtn;
    private Button nextBtn;
    private GifImageView gifImageView;
    private TextView textView;
    private int currentIndex = 0;
    private boolean flag = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initData();
        initView();
    }

    private void initView() {
        lastBtn = (Button)findViewById(R.id.last);
        nextBtn = (Button)findViewById(R.id.next);
        textView = (TextView)findViewById(R.id.textView);
        gifImageView = (GifImageView)findViewById(R.id.gifImageView);
        try {
            GifDrawable gifDrawable = new GifDrawable(getResources(), images.get(currentIndex));
            gifImageView.setImageDrawable(gifDrawable);
        } catch (IOException e) {
            e.printStackTrace();
        }

        textView.setText(String.format(getResources().getString(R.string.image_seq), currentIndex + 1));

        lastBtn.setOnClickListener(this);
        nextBtn.setOnClickListener(this);
    }

    private void initData() {
        images = new ArrayList<Integer>();
        int id;
        // 读取所有图片
        for(int i = 1; ; i++)
        {
            id = getResources().getIdentifier("emo_" + i, "drawable", getPackageName());
            if(id == 0)
                break;
            images.add(id);
        }
        Log.v("onCreate", images.toString());
    }

    @Override
    public void onClick(View view) {
        Log.v("flag", String.valueOf(flag));
        Log.v("currentIndex", String.valueOf(currentIndex));
//        Log.v("textView", String.format(getResources().getString(R.string.image_seq), currentIndex));
//        Log.v("resourceID", images.get(currentIndex).toString());
        if(view == lastBtn)
        {
            if(currentIndex == 0 && !flag)
            {
                flag = true;
                Toast.makeText(this, "已经是第一张了, 再点击一次后, 将会切换为最后一张", Toast.LENGTH_SHORT).show();
                return;
            }
            flag = false;
            if(--currentIndex < 0)
                currentIndex = images.size() - 1;
        }
        else if(view == nextBtn)
        {
            if(currentIndex == images.size() - 1 && !flag)
            {
                flag = true;
                Toast.makeText(this, "已经是最后一张了, 再点击一次后, 将会切换为第一张", Toast.LENGTH_SHORT).show();
                return;
            }
            flag = false;
            if(++currentIndex == images.size())
                currentIndex = 0;
        }
        textView.setText(String.format(getResources().getString(R.string.image_seq), currentIndex + 1));
        gifImageView.setImageResource(images.get(currentIndex));
    }
}
