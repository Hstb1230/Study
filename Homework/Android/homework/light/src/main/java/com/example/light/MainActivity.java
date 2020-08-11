package com.example.light;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements CompoundButton.OnCheckedChangeListener, View.OnClickListener {

    private ToggleButton btnToggle;
    private Switch btnSwitch;
    private ImageView img;
    private Button btnListAlert;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        img = (ImageView)findViewById(R.id.imageView);
        btnToggle = (ToggleButton)findViewById(R.id.toggleButton);
        btnSwitch = (Switch)findViewById(R.id.switch1);
        btnListAlert = (Button)findViewById(R.id.button);
        btnToggle.setOnCheckedChangeListener(this);
        btnSwitch.setOnCheckedChangeListener(this);
        btnListAlert.setOnClickListener(this);
    }

    @Override
    public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
        if(b)
            img.setImageResource(android.R.drawable.btn_star_big_on);
        else
            img.setImageResource(android.R.drawable.btn_star_big_off);
    }

    @Override
    public void onClick(View view) {
        if(view == btnListAlert)
        {
            AlertDialog.Builder alert = new AlertDialog.Builder(MainActivity.this);
            alert.setIcon(R.mipmap.ic_launcher);
            alert.setTitle("提示");
            String seq = "ABCDEFG";
            final ArrayList<String> list = new ArrayList<String>();
            for(int i = 0; i < seq.length(); i++)
            {
                list.add(seq.substring(i, seq.length()) + seq.substring(0, i));
            }
//            String item[] = list.toArray(new String[] {});
//            Log.v("String", Arrays.toString(item));
            alert.setItems(list.toArray(new String[] {}), new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialogInterface, int i) {
                    Toast.makeText(getApplicationContext(), "您选择的是 " + list.get(i).toString(), Toast.LENGTH_SHORT).show();
                }
            });
            alert.show();
        }
    }
}
