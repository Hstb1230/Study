package com.example.calculate;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.Gravity;
import android.widget.Button;
import android.widget.GridLayout;

public class MainActivity extends AppCompatActivity {
    private GridLayout gridLayout = null;
    final String symbol[] = new String[] {
            "7", "8", "9", "÷",
            "4", "5", "6", "×",
            "1", "2", "3", "－",
            "0", ".", "＋", "="
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        gridLayout = findViewById(R.id.root);
        for(int i = 0; i < symbol.length; i++) {
            Button btn = new Button(this);
            btn.setText(symbol[i]);
            btn.setTextSize(40);
            btn.setPadding(5, 35, 5, 35);
            // 指定行
            GridLayout.Spec rowSpec = GridLayout.spec(2 + (i / 4));
            // 指定列
            GridLayout.Spec colSpec = GridLayout.spec(i % 4);
            GridLayout.LayoutParams params = new GridLayout.LayoutParams(rowSpec, colSpec);
            // 指定组件占满父组件
            params.setGravity(Gravity.FILL);
            gridLayout.addView(btn, params);
        }
    }
}
