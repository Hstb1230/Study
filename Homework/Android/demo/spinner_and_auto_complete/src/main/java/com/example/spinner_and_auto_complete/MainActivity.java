package com.example.spinner_and_auto_complete;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.MultiAutoCompleteTextView;
import android.widget.Spinner;

public class MainActivity extends AppCompatActivity {
    private AutoCompleteTextView actv;
    private MultiAutoCompleteTextView mactv;
    private Spinner spinner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        actv = (AutoCompleteTextView)findViewById(R.id.auto);
        mactv = (MultiAutoCompleteTextView)findViewById(R.id.mAuto);
        String books[] = {
                "Java",
                "Java EE",
                "Java ME",
                "Android",
                "kill"
        };
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_dropdown_item_1line, books);
        actv.setAdapter(adapter);
        mactv.setAdapter(adapter);
        mactv.setTokenizer(new MultiAutoCompleteTextView.CommaTokenizer());
        spinner = (Spinner)findViewById(R.id.spinner2);
        String people[] = {
                "孙悟空", "猪八戒", "牛魔王"
        };
        ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(
                this, android.R.layout.simple_list_item_multiple_choice, people
        );
        spinner.setAdapter(adapter2);
    }
}
