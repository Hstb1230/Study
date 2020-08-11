package com.example.exam_reg;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class RegisterSuccessActivity
        extends AppCompatActivity
{

    private Button btnReturn;
    private TextView txtRegisterID;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register_success);

        initView();
        bindData();
        bindEvent();

    }

    private void bindEvent()
    {
        btnReturn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                Intent intent = new Intent(RegisterSuccessActivity.this, ExamListActivity.class);
//                startActivity(intent);
                setResult(1, intent);
                finish();
            }
        });
    }

    private int getRandomInt(int min, int max)
    {
        return (int)(min + Math.random() * (max - min + 1));
    }

    private void bindData()
    {
        txtRegisterID.setText(String.valueOf(getRandomInt(100000, 1000000)));
    }

    private void initView()
    {
        btnReturn = (Button) findViewById(R.id.registerSuccessReturn);
        txtRegisterID = (TextView) findViewById(R.id.registerSuccessID);
    }
}
