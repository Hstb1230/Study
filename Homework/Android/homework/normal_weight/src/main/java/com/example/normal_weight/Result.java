package com.example.normal_weight;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.Objects;

public class Result extends AppCompatActivity {

    private Button btnReturn;
    private TextView textSex;
    private TextView textWeight;
    private TextView textSuggestion;
    private ImageView image;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);

        textSex = (TextView)findViewById(R.id.textView5);
        textWeight = (TextView)findViewById(R.id.textView6);
        textSuggestion = (TextView)findViewById(R.id.textView7);
        image = (ImageView)findViewById(R.id.imageView2);
        btnReturn = (Button)findViewById(R.id.button2);
        btnReturn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

        Intent intent = getIntent();
        String sex = intent.getStringExtra("sex");
        assert sex != null;
        textSex.setText("您的性别是" + sex);
        double height = Double.parseDouble(Objects.requireNonNull(intent.getStringExtra("height")));
        double weight = Double.parseDouble(Objects.requireNonNull(intent.getStringExtra("weight")));
        double normalWeight;
        if(sex.equals("男"))
        {
            normalWeight = (height - 80) * 0.7;
            image.setImageResource(R.drawable.boy);
        }
        else
        {
            normalWeight = (height - 70) * 0.6;
            image.setImageResource(R.drawable.girl);
        }
        textWeight.setText("您的标准体重是" + String.valueOf(normalWeight) + "kg");
        double diff = (weight - normalWeight) / normalWeight;
        String result;
        if(diff < -0.3)
        {
            result = "您真的太轻了, 太轻不是件好事, 注意补充营养";
        }
        else if(diff < -0.2)
        {
            result = "您太瘦了, 这可不是件好事, 注意补充营养";
        }
        else if(diff < -0.1)
        {
            result = "您有点轻, 可以稍微补充营养";
        }
        else if(diff < 0.1)
        {
            result = "您的体重刚刚好, 注意保持";
        }
        else if(diff < 0.2)
        {
            result = "您还差一点就是完美身材了, 可以稍微锻炼下";
        }
        else if(diff < 0.3)
        {
            result = "您的体重不是特别刚好, 需要加强锻炼";
        }
        else if(diff < 0.5)
        {
            result = "您与完美身材还有一段距离, 平常要多锻炼, 加油";
        }
        else
        {
            result = "您离完美身材差的太远了, 需要经常锻炼, 控制饮食";
        }
        textSuggestion.setText(result);
    }
}
