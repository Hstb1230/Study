package com.example.exam_reg;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.Arrays;

public class HomeActivity extends AppCompatActivity {
    private Button btnReturn;
    private String username;
    private String toNewUsername = "";
    private EditText newUsername;
    private String[] existUsernameList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        Intent intent = getIntent();
        username = intent.getStringExtra("Username");
        existUsernameList = intent.getStringArrayExtra("ExistUsername");


        newUsername = (EditText)findViewById(R.id.home_new_username);

        btnReturn = (Button)findViewById(R.id.btnReturn);
        btnReturn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                Bundle bundle = new Bundle();
                bundle.putString("Username", username);
                intent.putExtras(bundle);
                setResult(RESULT_OK, intent);
                finish();
            }
        });
    }

    public void changeUsername(View view) {
        String inputNewUsername = newUsername.getText().toString();
        if(inputNewUsername.length() == 0)
        {
            Toast.makeText(getApplicationContext(), "新用户名不得为空", Toast.LENGTH_SHORT).show();
            newUsername.requestFocus();
        }
        else if(username.equals(inputNewUsername))
        {
            Toast.makeText(getApplicationContext(), "新用户名与原用户名一致", Toast.LENGTH_SHORT).show();
            newUsername.setText("");
            newUsername.requestFocus();
        }
        else if(Arrays.asList(existUsernameList).contains(inputNewUsername))
        {
            Toast.makeText(getApplicationContext(), "新用户名已存在", Toast.LENGTH_SHORT).show();
            newUsername.setText("");
            newUsername.requestFocus();
        }
        else
        {
            MainActivity.accounts.put(inputNewUsername, MainActivity.accounts.remove(username));
            username = inputNewUsername;
            Toast.makeText(getApplicationContext(), "用户名修改成功", Toast.LENGTH_SHORT).show();
        }
    }
}
