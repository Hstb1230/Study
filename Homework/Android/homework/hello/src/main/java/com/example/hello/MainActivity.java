package com.example.hello;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button btn1 = null;
    private Button btn2 = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn1 = (Button)findViewById(R.id.button1);
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(getApplicationContext(), "Welcome to Android", Toast.LENGTH_SHORT).show();
            }
        });

        btn2 = (Button)findViewById(R.id.button2);
        btn2.setOnClickListener(this);


    }

    @Override
    public void onClick(View view) {
        Toast.makeText(getApplicationContext(), "This is Java", Toast.LENGTH_LONG).show();
    }

    public void hello_2020(View view) {
        Toast.makeText(getApplicationContext(), "Hello 2019, Welcome to 2020", Toast.LENGTH_SHORT).show();
    }
}
