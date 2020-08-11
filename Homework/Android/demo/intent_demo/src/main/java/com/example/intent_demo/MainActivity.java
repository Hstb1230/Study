package com.example.intent_demo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    private Button btnDrug;
    private Button btnPay;
    private Button btnSMS;
    private Button btnStart;
    private Button btnUrl;
    private Button btnSecond;
    private Button btnThird;
    private Button btnSendBroadcast;
    private EditText editMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnDrug = (Button) findViewById(R.id.button3);
        btnPay = (Button) findViewById(R.id.button4);
        btnSMS = (Button) findViewById(R.id.button5);
        btnStart = (Button)  findViewById(R.id.button6);
        btnUrl = (Button)  findViewById(R.id.button7);
        btnSecond = (Button) findViewById(R.id.button8);
        btnThird = (Button) findViewById(R.id.button9);
        editMessage = (EditText) findViewById(R.id.editText);
        btnSendBroadcast = (Button) findViewById(R.id.button10);

        btnDrug.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://www.baidu.com"));
                startActivity(intent);
            }
        });
        btnPay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_CALL, Uri.parse("tel:10000"));
                if(ActivityCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Consider calling
                    //    ActivityCompat#requestPermissions
                    // here to request the missing permissions, and then overriding
                    //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                    //                                          int[] grantResults)
                    // to handle the case where the user grants the permission. See the documentation
                    // for ActivityCompat#requestPermissions for more details.
                    return;
                }
                startActivity(intent);
            }
        });
        btnSMS.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intentSMS = new Intent(Intent.ACTION_SENDTO, Uri.parse("smsto:10086"));
                intentSMS.putExtra("sms_body", "你个辣鸡");
                startActivity(intentSMS);
            }
        });
        btnStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent("com.example.intent_demo.action.SECOND");
                startActivity(intent);
            }
        });
        btnUrl.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent();
                intent.setData(Uri.parse("lalala://"));
                startActivity(intent);
            }
        });
        btnSecond.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent("com.demo.app.second");
                startActivity(intent);
            }
        });
        btnThird.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent();
                ComponentName component = new ComponentName("com.example.second_app", "com.example.second_app.ThirdActivity");
                intent.setComponent(component);
                startActivity(intent);
            }
        });
        btnSendBroadcast.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent("com.demo.app.broadcast");
                intent.putExtra("message", editMessage.getText().toString());
                sendBroadcast(intent);
            }
        });
    }
}
