package com.example.array_adapter;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

public class MainActivity
        extends AppCompatActivity
{

    private ListView list;
    private String[] courseList;
    private ArrayAdapter<String> adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initData();
        initView();
    }

    private void initData()
    {
        courseList = getResources().getStringArray(R.array.course);
        adapter = new ArrayAdapter<String>(getApplicationContext(), R.layout.item, courseList);
        list.setAdapter(adapter);
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l)
            {
                Toast.makeText(getApplicationContext(), courseList[i], Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void initView()
    {
        list = (ListView) findViewById(R.id.list);
    }
}
