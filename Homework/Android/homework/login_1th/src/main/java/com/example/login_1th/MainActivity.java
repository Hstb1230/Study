package com.example.login_1th;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private Button login;
    private Button exit;
    private EditText username;
    private EditText password;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        login = (Button)findViewById(R.id.login);
        exit = (Button)findViewById(R.id.exit);

        username = (EditText)findViewById(R.id.username);
        password = (EditText)findViewById(R.id.password);

        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String inputUsername = username.getText().toString();
                String inputPassword = password.getText().toString();
                if(!inputUsername.equals("admin")) {
                    Toast.makeText(MainActivity.this, "用户名错误", Toast.LENGTH_SHORT).show();
                    username.setText("");
                    username.requestFocus();
                } else if(!inputPassword.equals("666666")) {
                    Toast.makeText(MainActivity.this, "密码错误", Toast.LENGTH_SHORT).show();
                    password.setText("");
                    password.requestFocus();
                } else {
//                    Toast.makeText(MainActivity.this, "恭喜您 登录成功", Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent();
                    intent.setClass(getApplicationContext(), HomeActivity.class);
                    startActivity(intent);
                    
                    username.setText("");
                    password.setText("");
                }
            }
        });
        exit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });
    }
}
