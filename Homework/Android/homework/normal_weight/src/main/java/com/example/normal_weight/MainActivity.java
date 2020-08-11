package com.example.normal_weight;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class MainActivity extends AppCompatActivity {

    private RadioGroup radioSex;
    private EditText editHeight;
    private EditText editWeight;
    private Button btnCalculate;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        radioSex = (RadioGroup)findViewById(R.id.radioGroup1);
        editHeight = (EditText)findViewById(R.id.editText);
        editWeight = (EditText)findViewById(R.id.editText2);
        btnCalculate = (Button)findViewById(R.id.button);
        btnCalculate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), Result.class);
                intent.putExtra("sex", ((RadioButton)findViewById(radioSex.getCheckedRadioButtonId())).getText().toString());
                intent.putExtra("height", editHeight.getText().toString());
                intent.putExtra("weight", editWeight.getText().toString());
                startActivity(intent);
            }
        });
    }
}
