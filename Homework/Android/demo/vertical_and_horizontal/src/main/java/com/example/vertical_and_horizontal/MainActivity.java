package com.example.vertical_and_horizontal;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.ToggleButton;

public class MainActivity extends AppCompatActivity {
    ToggleButton toggle;
    Switch switcher;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        toggle = findViewById(R.id.toggle);
        switcher = findViewById(R.id.switcher);
        final LinearLayout button_group = findViewById(R.id.button_group);
        CompoundButton.OnCheckedChangeListener listener = new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                button_group.setOrientation(b ? LinearLayout.VERTICAL : LinearLayout.HORIZONTAL);
                toggle.setChecked(b);
                switcher.setChecked(b);
            }
        };
        toggle.setOnCheckedChangeListener(listener);
        switcher.setOnCheckedChangeListener(listener);
    }
}
