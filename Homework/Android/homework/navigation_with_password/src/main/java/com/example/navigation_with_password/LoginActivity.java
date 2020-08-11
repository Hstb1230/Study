package com.example.navigation_with_password;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.util.TypedValue;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.GridView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Arrays;

public class LoginActivity
        extends AppCompatActivity
{

    private LinearLayout passwordState;
    private GridView keyGrid;
    private String password;
    private String[] keyArray;
    private static final String truePassword = "666666";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        initData();
        initView();
        bindEvent();
    }

    private void bindEvent()
    {
        keyGrid.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l)
            {
                String input = ((TextView)keyGrid.getChildAt(i)).getText().toString();
                if(TextUtils.isDigitsOnly(input))
                {
                    password += input;
                }
                else if(input.equals("←") && password.length() > 0)
                {
                    password = password.substring(0, password.length() - 1);
                }

                Log.v("password", password);

                if(password.length() == truePassword.length())
                {
                    boolean loginSuccess = password.equals(truePassword);
                    password = "";
                    if(loginSuccess)
                    {
                        Toast.makeText(getApplicationContext(), "Login Success", Toast.LENGTH_SHORT).show();
                        Intent intent = new Intent(getApplicationContext(), NavigationActivity.class);
                        startActivity(intent);
                        finish();
                    }
                    else
                    {
                        Toast.makeText(getApplicationContext(), "密码错误, 请重新输入", Toast.LENGTH_SHORT).show();
                    }
                }
                refreshPasswordState();
            }
        });
    }

    /**
     * 刷新密码点数
     */
    private void refreshPasswordState()
    {
        for(int i = 0; i < password.length(); i++)
        {
            TextView state = (TextView) passwordState.getChildAt(i);
            state.setText(R.string.password_has);
        }
        for(int i = password.length(); i < truePassword.length(); i++)
        {
            TextView state = (TextView) passwordState.getChildAt(i);
            state.setText(R.string.password_none);
        }
    }

    private void initData()
    {
        password = "";
        keyArray = new String[12];
        int i = 0;
        for(char c : "123456789".toCharArray())
        {
            keyArray[i++] = String.valueOf(c);
        }
        keyArray[i++] = "Call";
        keyArray[i++] = "0";
        keyArray[i++] = "←";
        Log.v("keyArray", Arrays.toString(keyArray));
    }

    private void initView()
    {
        passwordState = (LinearLayout) findViewById(R.id.passwordState);
        passwordState.removeAllViews();
        for(int i = truePassword.length(); i > 0; i--)
        {
            TextView state = new TextView(getApplicationContext());
            state.setText(R.string.password_none);
            state.setTextColor(getResources().getColor(android.R.color.black));
            state.setTextSize(TypedValue.COMPLEX_UNIT_SP, 23);
            passwordState.addView(state);
        }
        keyGrid = (GridView) findViewById(R.id.key);

        ArrayAdapter<String> adapter = new ArrayAdapter<>(getApplicationContext(), R.layout.key_item, keyArray);
        keyGrid.setAdapter(adapter);
    }


}
