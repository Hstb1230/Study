package com.example.multi_thread;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.TextView;

public class MainActivity
        extends AppCompatActivity
{

    private TextView textNumber;
    private HandlerMe handler;


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textNumber = (TextView) findViewById(R.id.textNumber);
    }

    public void clickBtnStart(View view)
    {
        handler = new HandlerMe();
//        ThreadFresh fresh = new ThreadFresh();
        RunnableFresh runnableFresh = new RunnableFresh();
        Thread fresh = new Thread(runnableFresh);
        fresh.start();
    }

    class HandlerMe extends Handler
    {
        @Override
        public void handleMessage(@NonNull Message msg)
        {
            if(msg.what == 0x01)
            {
//                textNumber.setText(String.valueOf(Integer.parseInt(textNumber.getText().toString()) + 1));
                textNumber.setText(String.valueOf(msg.arg1));
            }
            super.handleMessage(msg);
        }
    }

//    class ThreadFresh extends Thread
    class RunnableFresh implements Runnable
    {
        @Override
        public void run()
        {
            for(int i = 0; i < 100; i++)
            {
                Message msg = new Message();
                msg.what = 0x01;
                msg.arg1 = i + 1;
                handler.sendMessage(msg);
                try
                {
                    Thread.sleep(50);
                } catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        }
    }
}
