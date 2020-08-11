package com.example.stable_fragment;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Objects;

public class MainActivity
        extends AppCompatActivity
{

    private TextView schoolTitleView;
    private ListView schoolListView;
    private String[] schoolNameList;
    private String[] schoolCodeList;
    private Fragment majorFragment;
    private ListView majorListView;
    private TextView majorTitleView;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initData();
        initView();
        bindData();
        bindEvent();

    }

    private void bindEvent()
    {
        schoolListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l)
            {
                schoolTitleView.setText("34所自划线学校");
                schoolTitleView.setTextColor(getResources().getColor(android.R.color.darker_gray));
                String schoolName = ((TextView) view.findViewById(R.id.schoolName)).getText().toString();
                String schoolCode = ((TextView) view.findViewById(R.id.schoolCode)).getText().toString();
                Log.i(schoolName, schoolCode);
                String[] majorList = getResources().getStringArray(getResources().getIdentifier(schoolCode, "array", getPackageName()));
                ArrayAdapter<String> adapter = new ArrayAdapter<String>(getApplicationContext(), R.layout.major_item, majorList);
                majorListView.setAdapter(adapter);
                majorTitleView.setText(String.format("工学专业(%d)", majorList.length));
                Objects.requireNonNull(majorFragment.getView()).setVisibility(View.VISIBLE);
            }
        });
    }

    private void bindData()
    {
        ArrayList< HashMap<String, Object> > schoolList = new ArrayList<>();
        for(int i = 0; i < schoolNameList.length; i++)
        {
            HashMap<String, Object> m = new HashMap<String, Object>();
            m.put("name", schoolNameList[i]);
            m.put("code", schoolCodeList[i]);
            schoolList.add(m);
        }
        SimpleAdapter adapter = new SimpleAdapter(
                getApplicationContext(), schoolList, R.layout.school_item, new String[] {"name", "code"}, new int[] {R.id.schoolName, R.id.schoolCode});
        schoolListView.setAdapter(adapter);
        Objects.requireNonNull(majorFragment.getView()).setVisibility(View.INVISIBLE);
    }

    private void initData()
    {
        schoolNameList = getResources().getStringArray(R.array.schools);
        schoolCodeList = getResources().getStringArray(R.array.school_sn);
    }

    private void initView()
    {
        schoolTitleView = (TextView) findViewById(R.id.listTitle);
        schoolListView = (ListView) findViewById(R.id.schoolList);
        majorFragment = (Fragment) getSupportFragmentManager().findFragmentById(R.id.majorFragment);
        assert majorFragment != null;
        majorTitleView = (TextView) Objects.requireNonNull(majorFragment.getView()).findViewById(R.id.majorTitle);
        majorListView = (ListView) Objects.requireNonNull(majorFragment.getView()).findViewById(R.id.majorList);
    }
}
