package com.example.name_and_sex;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private EditText name = null;
    private RadioButton sex_man = null;
    private RadioButton sex_woman = null;
    private TextView result = null;
    private RadioGroup sex_group = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        name = (EditText)findViewById(R.id.editText);
        sex_man = (RadioButton)findViewById(R.id.sex_man);
        sex_woman = (RadioButton)findViewById(R.id.sex_woman);
        result = (TextView)findViewById(R.id.textView3);
        sex_group = (RadioGroup)findViewById(R.id.sex_group);
        sex_group.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int i) {
                String str = "您输入的信息为\n姓名：" + name.getText() + "，性别：";
                if(sex_man.isChecked()) str += "男";
                else if(sex_woman.isChecked()) str += "女";
                result.setText(str);
            }
        });
    }
}
