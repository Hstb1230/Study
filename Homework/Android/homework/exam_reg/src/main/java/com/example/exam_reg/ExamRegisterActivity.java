package com.example.exam_reg;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;


public class ExamRegisterActivity
        extends AppCompatActivity
{
    public static AppCompatActivity instance = null;
    public static final int reqWithRegisterInfoCheck = 0x06;

    private String username;
    private String exam_type;
    private Spinner spinnerSchool;
    private Spinner spinnerMajor;
    private Spinner spinnerTeacher;
    private Button btnRegister;
    private String[] schoolSN;
    private String[] school;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_exam_register);

        instance = this;

        getData();
        initView();
        initData();
        bindData();
        bindEvent();
    }

    private void bindData()
    {
        String[] schools = getResources().getStringArray(R.array.schools);
        ArrayAdapter<String> schoolAdapter = new ArrayAdapter<String>(getApplicationContext(), R.layout.register_spinner, schools);
        spinnerSchool.setAdapter(schoolAdapter);

    }

    private void initData()
    {
        school = getResources().getStringArray(R.array.schools);
        schoolSN = getResources().getStringArray(R.array.school_sn);
    }

    private int getRandomInt(int min, int max)
    {
        return (int)(min + Math.random() * (max - min + 1));
    }

    private void bindEvent()
    {
        spinnerSchool.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int index, long l)
            {
                Log.v(String.valueOf(index), schoolSN[index]);
//                Toast.makeText(getApplicationContext(), String.valueOf(i) + " " + schoolSN[i], Toast.LENGTH_SHORT).show();
                int id = getResources().getIdentifier(schoolSN[index], "array", getPackageName());
                String[] majors = getResources().getStringArray(id);
//                Log.v("getIdentifier", String.valueOf(id));
                ArrayAdapter<String> majorAdapter = new ArrayAdapter<String>(getApplicationContext(), R.layout.register_spinner, majors);
                spinnerMajor.setAdapter(majorAdapter);
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView)
            {

            }
        });

        spinnerMajor.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int index, long l)
            {

                String[] teacher = new String[getRandomInt(3, 8)];
                for(int i = 0; i < teacher.length; i++)
                {
                    teacher[i] = "";
                    teacher[i] = String.valueOf((char)('A' + getRandomInt(0, 25)))
                                 + String.valueOf((char)('A' + getRandomInt(0, 25)))
                                 + String.valueOf((char)('A' + getRandomInt(0, 25)));
                }
                ArrayAdapter<String> teacherAdapter = new ArrayAdapter<String>(getApplicationContext(), R.layout.register_spinner, teacher);
                spinnerTeacher.setAdapter(teacherAdapter);
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView)
            {

            }
        });

        btnRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                Intent intent = new Intent(ExamRegisterActivity.this, RegisterInfoCheckActivity.class);
                intent.putExtra("username", username);
                intent.putExtra("school", spinnerSchool.getSelectedItem().toString());
                intent.putExtra("major", spinnerMajor.getSelectedItem().toString());
                intent.putExtra("teacher", spinnerTeacher.getSelectedItem().toString());
                startActivityForResult(intent, reqWithRegisterInfoCheck);
            }
        });
    }

    private void initView()
    {
        spinnerSchool = (Spinner) findViewById(R.id.registerSchool);
        spinnerMajor = (Spinner) findViewById(R.id.registerMajor);
        spinnerTeacher = (Spinner) findViewById(R.id.registerTeacher);
        btnRegister = (Button) findViewById(R.id.regContinue);
    }

    private void getData()
    {
        Intent intent = getIntent();
        username = intent.getStringExtra("username");
        exam_type = intent.getStringExtra("exam_type");
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent intent) {
        switch(requestCode)
        {
            case reqWithRegisterInfoCheck:
                if(resultCode == RESULT_OK)
                {
                    finish();
                }
                break;
            default:
                super.onActivityResult(requestCode, resultCode, intent);
        }
    }

}
