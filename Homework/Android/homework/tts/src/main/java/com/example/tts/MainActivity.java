package com.example.tts;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Locale;

public class MainActivity
        extends AppCompatActivity
{

    private Button btnSay;
    private TextView toSayTextView;
    private TextToSpeech mSpeech;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
        bindEvent();

    }

    private void bindEvent()
    {
        btnSay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                String text = toSayTextView.getText().toString();
                if(TextUtils.isDigitsOnly(text))
                {
                    StringBuilder tmp = new StringBuilder();
                    for(char c : text.toCharArray())
                    {
                        tmp.append(c);
                        tmp.append(" ");
                    }
                    text = tmp.toString();
                }
                mSpeech.speak(text, TextToSpeech.QUEUE_FLUSH, null);
            }
        });
    }

    private void initView()
    {
        btnSay = (Button) findViewById(R.id.btnSay);
        toSayTextView = (TextView) findViewById(R.id.toSayTextView);
        mSpeech = new TextToSpeech(getApplicationContext(), new TextToSpeech.OnInitListener()
        {
            @Override
            public void onInit(int status)
            {
                String tip;
                if(status == TextToSpeech.SUCCESS)
                {

                    int supported = mSpeech.setLanguage(Locale.SIMPLIFIED_CHINESE);

                    if((supported != TextToSpeech.LANG_AVAILABLE) && (supported != TextToSpeech.LANG_COUNTRY_AVAILABLE))
                    {
                        tip = "不支持当前语言！";
                    }
                    else
                    {
                        tip = "Initialize Success";
                    }

                }
                else
                {
                    tip = "Initialize Failed";
                }
                Toast.makeText(getApplicationContext(), tip, Toast.LENGTH_SHORT).show();
            }
        });
    }
}
