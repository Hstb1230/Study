package com.example.exam_reg;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class RegisterInfoCheckActivity
        extends AppCompatActivity
{

    private String school;
    private String major;
    private String teacher;
    private TextView txtSchool;
    private TextView txtMajor;
    private TextView txtTeacher;
    private Button btnReturn;
    private Button btnContinue;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register_info_check);

        getData();
        initView();
        bindData();

    }

    private void bindData()
    {
        txtSchool.setText(school);
        txtMajor.setText(major);
        txtTeacher.setText(teacher);
        btnReturn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
//                Intent intent = new Intent(RegisterInfoCheckActivity.this, )
                finish();
            }
        });
        btnContinue.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                ExamRegisterActivity.instance.finish();
                Intent intent = new Intent(RegisterInfoCheckActivity.this, RegisterSuccessActivity.class);
                startActivity(intent);
                finish();
            }
        });
    }

    private void initView()
    {
        txtSchool = (TextView) findViewById(R.id.checkSchool);
        txtMajor = (TextView) findViewById(R.id.checkMajor);
        txtTeacher = (TextView) findViewById(R.id.checkTeacher);
        btnReturn = (Button) findViewById(R.id.checkReturn);
        btnContinue = (Button) findViewById(R.id.checkContinue);
    }

    private void getData()
    {
        Intent intent = getIntent();
        intent.getStringExtra("username");
        school = intent.getStringExtra("school");
        major = intent.getStringExtra("major");
        teacher = intent.getStringExtra("teacher");
    }
}
