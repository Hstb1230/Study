package com.example.image_with_transparent;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {
    // 图片数组
    int[] image = new int[] {
            R.drawable.shock,
            R.drawable.sudden_hit,
            R.drawable.warning,
            R.drawable.dalao,
            R.drawable.iterative_analysis,
            R.drawable.liukanshan_2,
            R.drawable.liukanshan_emo_8,
            R.drawable.pangzi
    };
    // 默认显示图片
    int currentImageIndex = 2;
    // 图片的初始化透明度
    private int alpha = 255;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final Button btnPlus = (Button)findViewById(R.id.btnPlus);
        final Button btnMinus = (Button)findViewById(R.id.btnMinus);
        final Button btnNext = (Button)findViewById(R.id.btnNext);
        final ImageView img1 = (ImageView)findViewById(R.id.img1);
        final ImageView img2 = (ImageView)findViewById(R.id.img2);
        // 定义点击查看下一张图片的监听器
        btnNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 控制ImageView显示下一张图片
                img1.setImageResource(image[++currentImageIndex % image.length]);
                Log.i("onClick", Integer.toString(currentImageIndex % image.length));
            }

        });
        // 定义改变图片透明度的监听器
        View.OnClickListener transparencyListener = new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(view == btnPlus)
                    alpha += 20;
                else if (view == btnMinus)
                    alpha -= 20;
                if(alpha > 255)
                    alpha = 255;
                else if(alpha < 0)
                    alpha = 0;
                img1.setImageAlpha(alpha);
            }
        };
        btnPlus.setOnClickListener(transparencyListener);
        btnMinus.setOnClickListener(transparencyListener);


        img1.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                switch (motionEvent.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        view.performClick();
                        break;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        break;
                }
                // 获取img1的位图
                BitmapDrawable bitmapDrawable = (BitmapDrawable)img1.getDrawable();
                Bitmap bitmap = bitmapDrawable.getBitmap();
                // 获得实际缩放比例
                double scale = 1.0 * bitmap.getHeight() / img1.getHeight();
                // 获取需要显示的图片的开始点
                int x = (int)(motionEvent.getX() * scale);
                int y = (int)(motionEvent.getY() * scale);
                if(x + 120 > bitmap.getWidth())
                    x = bitmap.getWidth() - 120;
                if(y + 120 > bitmap.getHeight())
                    y = bitmap.getHeight() - 120;
                // 显示图片的指定区域
                Log.i("onTouch: ", x + "," + y);
                if(x < 0 || y < 0)
                    img2.setImageBitmap(Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight()));
                else
                    img2.setImageBitmap(Bitmap.createBitmap(bitmap, x, y, 120, 120));
                img2.setImageAlpha(alpha);
                return true;
            }
        });
    }
}
