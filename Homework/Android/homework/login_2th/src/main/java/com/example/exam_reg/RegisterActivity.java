package com.example.exam_reg;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.Arrays;

public class RegisterActivity extends AppCompatActivity implements View.OnClickListener {

    private Intent intent;
    private EditText username;
    private EditText password;
    private Button btnRegister;
    private String[] existUsernameList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);
        intent = getIntent();

        username = (EditText)findViewById(R.id.register_username);
        password = (EditText)findViewById(R.id.register_password);

        btnRegister = (Button)findViewById(R.id.register_register);

        username.setText(intent.getStringExtra("Username"));
        password.setText(intent.getStringExtra("Password"));

        existUsernameList = intent.getStringArrayExtra("ExistUsername");

    }

    public void register(View view) {
        String inputUsername = username.getText().toString();
        String inputPassword = password.getText().toString();
        if(inputUsername.length() == 0)
        {
            Toast.makeText(getApplicationContext(), "用户名不能为空", Toast.LENGTH_SHORT).show();
            username.requestFocus();
        }
        else if(inputPassword.length() == 0)
        {
            Toast.makeText(getApplicationContext(), "密码不能为空", Toast.LENGTH_SHORT).show();
            password.requestFocus();
        }
        else if(Arrays.asList(existUsernameList).contains(inputUsername))
        {
            Toast.makeText(getApplicationContext(), "用户名已存在", Toast.LENGTH_SHORT).show();
            username.setText("");
            username.requestFocus();
        }
        else
        {
            MainActivity.accounts.put(inputUsername, inputPassword);
            Toast.makeText(getApplicationContext(), "注册成功", Toast.LENGTH_SHORT).show();
            Intent intent = new Intent(getApplicationContext(), MainActivity.class);
            Bundle bundle = new Bundle();
            bundle.putString("Username", inputUsername);
            bundle.putString("Password", inputPassword);
            intent.putExtras(bundle);
            setResult(RESULT_OK, intent);
            finish();
        }
    }

    @Override
    public void onClick(View view) {

    }
}
