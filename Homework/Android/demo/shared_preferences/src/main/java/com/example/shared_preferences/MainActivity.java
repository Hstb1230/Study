package com.example.shared_preferences;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;

public class MainActivity
        extends AppCompatActivity
{

    private EditText editUsername;
    private EditText editPassword;
    private Button btnLogin;
    private Button btnExit;
    private SharedPreferences sharedPreferences;
    private CheckBox checkSavePassword;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
        initData();
        bindData();
        bindEvent();
    }

    private void bindData()
    {
        editUsername.setText(sharedPreferences.getString("username", ""));
        editPassword.setText(sharedPreferences.getString("password", ""));
    }

    private void initData()
    {
        sharedPreferences = getSharedPreferences("login", Context.MODE_PRIVATE);
    }

    private void bindEvent()
    {
        btnExit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                finish();
            }
        });
        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                if(checkSavePassword.isChecked())
                {
                    SharedPreferences.Editor edit = sharedPreferences.edit();
                    edit.putString("username", editUsername.getText().toString());
                    edit.putString("password", editPassword.getText().toString());
                    edit.apply();
                }
            }
        });
    }

    private void initView()
    {
         editUsername = (EditText) findViewById(R.id.editUsername);
         editPassword = (EditText) findViewById(R.id.editPassword);
         btnLogin = (Button) findViewById(R.id.btnLogin);
         btnExit = (Button) findViewById(R.id.btnExit);
         checkSavePassword = (CheckBox) findViewById(R.id.checkSavePassword);
    }
}
