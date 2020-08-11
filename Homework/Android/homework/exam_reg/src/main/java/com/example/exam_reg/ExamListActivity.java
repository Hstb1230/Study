package com.example.exam_reg;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class ExamListActivity
        extends AppCompatActivity
{

    private ListView listView;
    private String[] eduNameList;
    private String[] eduNamePinYinList;
    private int[] eduImgList;
    private ArrayList<Map<String, Object>> eduList;
    private SimpleAdapter simpleAdapter;
    private String username;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_exam_list);



        getData();
        initView();
        initData();
        bindEvent();
    }

    private void getData()
    {
        Intent intent = getIntent();
        username = intent.getStringExtra("Username");
    }

    private void bindEvent()
    {
    }

    private void initData()
    {
        eduNameList = getResources().getStringArray(R.array.edu_list);
        eduNamePinYinList = getResources().getStringArray(R.array.edu_list_pinyin);
        eduImgList = new int[eduNamePinYinList.length];
        int i = 0;
        for(String pin: eduNamePinYinList)
        {
            eduImgList[i] = getResources().getIdentifier("edu_" + pin.replace(" ", "_"), "drawable", getPackageName());
            i++;
        }
        eduList = new ArrayList<Map<String, Object>>();
        for(i = 0; i < eduNameList.length; i++)
        {
            Map<String, Object> map = new HashMap<>();
            map.put("img", eduImgList[i]);
            map.put("name", eduNameList[i]);
            map.put("people", "目前已报名" + String.valueOf((int)(10000 + Math.random()*(100000 - 10000 + 1))) + "人");
            eduList.add(map);
        }
        simpleAdapter = new SimpleAdapter(this,
                                          eduList,
                                          R.layout.exam_item,
                                          new String[] {"img", "name", "people"},
                                          new int[] {R.id.edu_img, R.id.edu_name, R.id.edu_people}
        )
        {
            @Override
            public View getView(final int position, View convertView, ViewGroup parent)
            {
                final View view = super.getView(position, convertView, parent);
                view.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view)
                    {
                        Toast.makeText(getApplicationContext(), String.valueOf(position), Toast.LENGTH_SHORT).show();
                    }
                });
                Button btnEnter = (Button) view.findViewById(R.id.edu_start);
                btnEnter.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view)
                    {
                        if(eduNameList[position].equals("硕士"))
                        {
                            Intent intent = new Intent(ExamListActivity.this, ExamRegisterActivity.class);
                            intent.putExtra("username", username);
                            intent.putExtra("exam_type", "硕士");
                            startActivity(intent);
                        }
                        else
                        {
                            Toast.makeText(
                                    getApplicationContext(),
                                    "你选择的是" + eduNameList[position] + ", 该模块正在开发中",
                                    Toast.LENGTH_SHORT
                            ).show();
                        }
                    }
                });
                return view;
            }
        };
        listView = (ListView) findViewById(R.id.exam_list);
        listView.setAdapter(simpleAdapter);
    }

    private void initView()
    {
    }
}
