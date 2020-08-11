package com.example.movie_and_hobby;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private RadioGroup radioGroup;
    private Button btn1;
    private Button btn2;
    private CheckBox[] checkGroup;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
        bindEvent();

    }

    private void bindEvent() {
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int check = radioGroup.getCheckedRadioButtonId();
                Log.d("check", String.valueOf(check));
                if(check <= 0) {
                    Toast.makeText(getApplicationContext(), "您还没选择电影", Toast.LENGTH_SHORT).show();
                    return;
                }
                RadioButton radio = (RadioButton) findViewById(check);
                Toast.makeText(getApplicationContext(), "您喜欢的电影是: "+ radio.getText(), Toast.LENGTH_SHORT).show();
            }
        });
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final StringBuilder hobby = new StringBuilder();
                int flag = 0;
                for (CheckBox checkBox : checkGroup) {
                    if (checkBox.isChecked()) {
                        if (flag++ > 0)
                            hobby.append("、");
                        hobby.append(checkBox.getText().toString().replace(" ", ""));
                    }
                }
                if(flag == 0)
                    hobby.append("无");

                AlertDialog.Builder alert = new AlertDialog.Builder(MainActivity.this);
                alert.setIcon(R.mipmap.ic_launcher);
                alert.setTitle("提示");
                alert.setMessage("爱好选好了吗？");
                alert.setPositiveButton("选好了", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int none) {
                        Toast.makeText(getApplicationContext(), "您的爱好：" + hobby.toString(), Toast.LENGTH_SHORT).show();
                    }
                });
                alert.setNegativeButton("再想想", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        Toast.makeText(getApplicationContext(), "好的", Toast.LENGTH_SHORT).show();
                    }
                });
                alert.show();
            }
        });
    }

    private void initView() {
        radioGroup = (RadioGroup)findViewById(R.id.radioGroup1);
        btn1 = (Button)findViewById(R.id.button);
        btn2 = (Button)findViewById(R.id.button1);
        checkGroup = new CheckBox[] {
                (CheckBox)findViewById(R.id.checkBox),
                (CheckBox)findViewById(R.id.checkBox2),
                (CheckBox)findViewById(R.id.checkBox3),
        };
    }
}
