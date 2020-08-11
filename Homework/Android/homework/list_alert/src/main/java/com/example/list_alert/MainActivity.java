package com.example.list_alert;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.util.Arrays;

public class MainActivity
        extends AppCompatActivity
{

    private Button btnSingle;
    private Button btnMult;
    private String[] singleList;
    private int singleChoose = 0;
    private String[] multList;
    private boolean[] multChoice;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
        createData();
        bindEvent();
    }

    private void createData()
    {
        singleList = new String[] {
                "a", "b", "c", "d", "e"
        };
        multList = new String[] {
                "aa", "ab", "ac", "ba", "bb", "bc"
        };
        multChoice = new boolean[multList.length];
        Arrays.fill(multChoice, false);
    }

    private void bindEvent()
    {
        btnSingle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                final AlertDialog.Builder dialog = new AlertDialog.Builder(MainActivity.this);
                dialog.setIcon(R.mipmap.ic_launcher);
                dialog.setTitle("请选择其中一项");
                dialog.setSingleChoiceItems(singleList, singleChoose, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        singleChoose = i;
                    }
                });
                dialog.setPositiveButtonIcon(getResources().getDrawable(R.drawable.ok));
                dialog.setPositiveButton("", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        Toast.makeText(getApplicationContext(), singleList[singleChoose], Toast.LENGTH_SHORT).show();
                    }
                });
                dialog.setNegativeButtonIcon(getResources().getDrawable(R.drawable.cancel));
                dialog.setNegativeButton("", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        Toast.makeText(getApplicationContext(), "您放弃选择", Toast.LENGTH_SHORT).show();
                    }
                });
                dialog.show();
            }
        });
        btnMult.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                final AlertDialog.Builder dialog = new AlertDialog.Builder(MainActivity.this);
                dialog.setIcon(R.mipmap.ic_launcher);
                dialog.setTitle("请选择其中几项");
                dialog.setMultiChoiceItems(multList, multChoice, new DialogInterface.OnMultiChoiceClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i, boolean b)
                    {
                        multChoice[i] = b;
                    }
                });
                dialog.setPositiveButtonIcon(getResources().getDrawable(R.drawable.mult));
                dialog.setPositiveButton("", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int index)
                    {
                        StringBuilder choiceContent = new StringBuilder();
                        choiceContent.setLength(0);
                        for(int i = 0; i < multChoice.length; i++)
                        {
                            if(multChoice[i])
                            {
                                if(!choiceContent.toString().equals(""))
                                    choiceContent.append("; ");
                                choiceContent.append(multList[i]);
                            }
                        }
                        if(choiceContent.length() == 0)
                        {
                            choiceContent.append("您未选择任何内容");
                        }
                        else
                        {
                            choiceContent.insert(0, "您选择的是: ");
                        }
                        Arrays.fill(multChoice, false);
                        Toast.makeText(getApplicationContext(), choiceContent.toString(), Toast.LENGTH_SHORT).show();
                    }
                });
                dialog.setNegativeButtonIcon(getResources().getDrawable(R.drawable.cancel));
                dialog.setNegativeButton("", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        Toast.makeText(getApplicationContext(), "您放弃选择", Toast.LENGTH_SHORT).show();
                    }
                });
                dialog.show();
            }
        });
    }

    private void initView()
    {
        btnSingle = (Button) findViewById(R.id.btnSingle);
        btnMult = (Button) findViewById(R.id.btnMult);
    }
}
