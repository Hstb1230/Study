package com.example.simple_chat;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;

import java.io.File;

public class ImageViewActivity
        extends AppCompatActivity
{

    private ImageView image;
    private String imgSrc;
    private LinearLayout background;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_view);

        initData();
        initView();
        bindData();
        bindEvent();
    }

    private void bindEvent()
    {
        background.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                finish();
            }
        });
    }

    private void bindData()
    {
        Uri uri = Uri.fromFile(new File(imgSrc));
        image.setImageURI(uri);
    }

    private void initData()
    {
        Intent intent = getIntent();
        imgSrc = intent.getStringExtra("img");
    }

    private void initView()
    {
        image = (ImageView) findViewById(R.id.image);
        background = (LinearLayout) findViewById(R.id.imageBackground);
    }
}
