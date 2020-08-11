package com.example.simple_adapter;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private int headers[];
    private String names[];
    private String descriptions[];
    private ListView listView;
    private ListView listView2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        headers = new int[] {
                R.drawable.huya,
                R.drawable.libai,
                R.drawable.liqingzhao,
                R.drawable.nongyu,
                R.drawable.aha
        };
        names = getResources().getStringArray(R.array.name);
        descriptions = getResources().getStringArray(R.array.description);
        List<Map<String, Object>> list = new ArrayList<Map<String, Object>>();
        for(int i = 0; i < names.length; i++) {
            Map<String, Object> item = new HashMap<String, Object>();
            item.put("header", headers[i]);
            item.put("name", names[i]);
            item.put("description", descriptions[i]);
            list.add(item);
        }
        SimpleAdapter simpleAdapter = new SimpleAdapter(
                this, list, R.layout.simple_item,
                new String[] {"header", "name", "description"},
                new int[] {R.id.header, R.id.name, R.id.description}
                );
        listView = (ListView)findViewById(R.id.listView);
        listView.setAdapter(simpleAdapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Log.v(String.valueOf(i), String.valueOf(l));
                Toast.makeText(getApplicationContext(), names[i] + "被单击了", Toast.LENGTH_SHORT).show();
            }
        });
        listView.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                Toast.makeText(getApplicationContext(), names[i] + "被选中了", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {

            }
        });

        listView2 = (ListView)findViewById(R.id.ListView2);
        BaseAdapter baseAdapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return 23;
            }

            @Override
            public Object getItem(int i) {
                return null;
            }

            @Override
            public long getItemId(int i) {
                return i;
            }

            @SuppressLint("SetTextI18n")
            @Override
            public View getView(int i, View view, ViewGroup viewGroup) {
                LinearLayout linearLayout = new LinearLayout(MainActivity.this);
                linearLayout.setOrientation(LinearLayout.HORIZONTAL);
                ImageView image = new ImageView(MainActivity.this);
                image.setImageResource(headers[i % headers.length]);
                TextView text = new TextView(MainActivity.this);
                text.setText("第 " + (i + 1) + " 个列表项");
                text.setTextSize(20);
                text.setTextColor(getResources().getColor(R.color.colorAccent));
                linearLayout.addView(image);
                linearLayout.addView(text);
                return linearLayout;
            }
        };
        listView2.setAdapter(baseAdapter);
    }
}
