package com.example.sex_and_color;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TextView result = null;
    private RadioButton sex_man, sex_woman;
    private CheckBox color_red, color_green, color_blue;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        result = findViewById(R.id.result);
        RadioGroup sex_group = findViewById(R.id.sex_group);
        sex_group.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int i) {
                sex_man = findViewById(R.id.sex_man);
                sex_woman = findViewById(R.id.sex_woman);
                refreshResult();
            }
        });
        color_red = findViewById(R.id.color_red);
        color_red.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                refreshResult();
            }
        });
        color_green = findViewById(R.id.color_green);
        color_green.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                refreshResult();
            }
        });
        color_blue = findViewById(R.id.color_blue);
        color_blue.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                refreshResult();
            }
        });
    }
    protected void refreshResult() {
        String str = "";
        if(sex_man != null && sex_woman != null) {
            str += "您的性别: ";
            if(sex_man.isChecked())
                str += "男";
            else if(sex_woman.isChecked())
                str += "女";
            str += "\n";
        }
        str += "喜欢的颜色：";
        boolean flag = false;
        if(color_red.isChecked()) {
            str += "红色";
            flag = true;
        }
        if(color_green.isChecked()) {
            if(flag)
                str += "，";
            str += "绿色";
            flag = true;
        }
        if(color_blue.isChecked()) {
            if(flag)
                str += "，";
            str += "蓝色";
            flag = true;
        }
        if(!flag)
            str += "无";
        str += "。";
        result.setText(str);
    }
}
