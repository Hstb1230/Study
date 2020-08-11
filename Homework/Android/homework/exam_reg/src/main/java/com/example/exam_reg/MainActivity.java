package com.example.exam_reg;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.HashMap;
import java.util.Objects;

public class MainActivity extends AppCompatActivity {
    public static final int reqWithRegister = 0x01;
    public static final int reqWithHome = 0x02;

    private Button login;
    private Button exit;
    private EditText username;
    private EditText password;
    public static HashMap<String, String> accounts;
    private Button register;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        login = (Button)findViewById(R.id.login);
        register = (Button)findViewById(R.id.register);
        exit = (Button)findViewById(R.id.exit);

        username = (EditText)findViewById(R.id.username);
        password = (EditText)findViewById(R.id.password);

//        username.setText("admin");
//        password.setText("666666");

        accounts = new HashMap<String, String>();
        accounts.put("admin", "666666");

        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String inputUsername = username.getText().toString();
                String inputPassword = password.getText().toString();
                if(inputUsername.length() == 0 || inputPassword.length() == 0)
                    return;
                if(accounts.containsKey(inputUsername))
                {
                    if(Objects.equals(accounts.get(inputUsername), inputPassword))
                    {
                        Intent intent = new Intent(getApplicationContext(), ExamListActivity.class);
                        Bundle bundle = new Bundle();
                        bundle.putString("Username", inputUsername);
                        bundle.putString("Password", inputPassword);
//                        bundle.putStringArray("ExistUsername", accounts.keySet().toArray(new String[0]));
                        intent.putExtras(bundle);
                        startActivity(intent);
                        finish();
//                        username.setText("");
//                        password.setText("");
                    }
                    else
                    {
                        Toast.makeText(getApplicationContext(), "密码错误", Toast.LENGTH_SHORT).show();
                        password.setText("");
                        password.requestFocus();
                    }
                }
                else
                {
                    AlertDialog.Builder dialog = new AlertDialog.Builder(MainActivity.this);
                    dialog.setIcon(R.mipmap.ic_launcher);
                    dialog.setTitle("用户不存在");
                    dialog.setMessage("是否注册?");
//                    dialog.setPositiveButtonIcon(getResources().getDrawable(R.drawable.reconnect));
                    dialog.setPositiveButton("注册", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int i) {
                            register.callOnClick();
                        }
                    });
//                    dialog.setNegativeButtonIcon(getResources().getDrawable(R.drawable.unlink));
                    dialog.setNegativeButton("取消", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int i) {
                        }
                    });
                    dialog.show();
                }

            }
        });

        register.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view) {
//                Toast.makeText(getApplicationContext(), "Click Register", Toast.LENGTH_SHORT).show();
                String inputUsername = username.getText().toString();
                String inputPassword = password.getText().toString();
                Intent intent = new Intent(getApplicationContext(), AccountRegisterActivity.class);
                Bundle bundle = new Bundle();
                bundle.putString("Username", inputUsername);
                bundle.putString("Password", inputPassword);
//                String[] existUsername = accounts.keySet().toArray(new String[0]);
                bundle.putStringArray("ExistUsername", accounts.keySet().toArray(new String[0]));
                intent.putExtras(bundle);
                startActivityForResult(intent, reqWithRegister);
            }
        });

        exit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent intent) {
        switch(requestCode)
        {
            case reqWithRegister:
                if(resultCode == RESULT_OK)
                {
                    assert intent != null;
                    Bundle bundle = intent.getExtras();
                    assert bundle != null;
//                    accounts.put(bundle.getString("Username"), bundle.getString("Password"));
                    username.setText(bundle.getString("Username"));
                    password.setText("");
                }
                break;
            case reqWithHome:
                if(resultCode == RESULT_OK)
                {
                    assert intent != null;
                    Bundle bundle = intent.getExtras();
                    assert bundle != null;
                    if(bundle.containsKey("Username"))
                    {
                        username.setText(bundle.getString("Username"));
                    }
                }

                break;
            default:
                super.onActivityResult(requestCode, resultCode, intent);
        }
    }
}
