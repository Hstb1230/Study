package com.example.dynamic_fragment;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;

public class MainActivity
        extends AppCompatActivity
{

    private Button btnShow;
    private LinearLayout leftView;

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
        btnShow.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                leftView.setLayoutParams(new LinearLayout.LayoutParams(getWindowManager().getDefaultDisplay().getWidth() / 3, getWindowManager().getDefaultDisplay().getHeight()));

                FragmentManager fragmentManager = getSupportFragmentManager();
                FragmentTransaction transaction = fragmentManager.beginTransaction();
                transaction.replace(R.id.main, new BlankFragment());
                transaction.addToBackStack(null);
                transaction.commit();
            }
        });
    }

    private void initView()
    {
        btnShow = (Button) findViewById(R.id.btnShow);
        leftView = (LinearLayout) findViewById(R.id.leftVIew);
    }
}
