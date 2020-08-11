package com.example.file_opt;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class MainActivity
        extends AppCompatActivity
{

    private EditText editInput;
    private TextView textContent;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
    }

    private void initView()
    {
        editInput = (EditText) findViewById(R.id.editInput);
        textContent = (TextView) findViewById(R.id.textContent);
    }

    public void systemStorageWrite(View view)
    {
        String txt = editInput.getText().toString();
        FileOutputStream fOut = null;
        try
        {
            fOut = openFileOutput("text", MODE_PRIVATE);
            fOut.write(txt.getBytes());
        } catch(IOException e)
        {
            e.printStackTrace();
            Toast.makeText(getApplicationContext(), "Write Content to System Strong Failed", Toast.LENGTH_SHORT).show();
        } finally
        {
            if(fOut != null)
            {
                Toast.makeText(getApplicationContext(), "Write Content to System Strong successfully", Toast.LENGTH_SHORT).show();
                try
                {
                    fOut.close();
                } catch(IOException e)
                {
                    e.printStackTrace();
                }
            }
        }
    }

    public void systemStorageRead(View view)
    {
        FileInputStream fIn = null;
        StringBuilder content = new StringBuilder();
        try
        {
            fIn = openFileInput("text");
            byte[] b = new byte[fIn.available() + 1];
            int readLength;
            do
            {
                readLength = fIn.read(b);
                if(readLength > 0)
                {
                    content.append(new String(b, 0, readLength));
                }
            }
            while(readLength != -1);
        } catch(IOException e)
        {
            e.printStackTrace();
            Toast.makeText(getApplicationContext(), "Read Content from System Strong Failed", Toast.LENGTH_SHORT).show();
        } finally
        {
            if(fIn != null)
            {
                Toast.makeText(getApplicationContext(), "Read Content from System Strong successfully", Toast.LENGTH_SHORT).show();
                try
                {
                    fIn.close();
                } catch(IOException e)
                {
                    e.printStackTrace();
                } finally
                {
                    textContent.setText(content.toString());
                }
            }
        }
    }

    public void extraStorageWrite(View view)
    {
        if(!Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED))
        {
            Toast.makeText(getApplicationContext(), "Extra Storage is not exist", Toast.LENGTH_SHORT).show();
            return;
        }
        String txt = editInput.getText().toString();
        String dir = Environment.getExternalStorageDirectory().toString();
        File f = new File(dir + File.separator + "text.txt");
        FileOutputStream fos = null;
        try
        {
            fos = new FileOutputStream(f);
            fos.write(txt.getBytes());
        } catch(IOException e)
        {
            e.printStackTrace();
            Toast.makeText(getApplicationContext(), "Write Content to Extra Storage Failed", Toast.LENGTH_SHORT).show();
        } finally
        {
            if(fos != null)
            {
                try
                {
                    fos.close();
                } catch(IOException e)
                {
                    e.printStackTrace();
                }
                Toast.makeText(getApplicationContext(), "Write Content to Extra Storage Successfully", Toast.LENGTH_SHORT).show();
            }
        }
    }

    public void extraStorageRead(View view)
    {
        if(!Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED))
        {
            Toast.makeText(getApplicationContext(), "Extra Storage is not exist", Toast.LENGTH_SHORT).show();
            return;
        }
        String dir = Environment.getExternalStorageDirectory().toString();
        File f = new File(dir + File.separator + "text.txt");
        Toast.makeText(getApplicationContext(), f.getAbsolutePath(), Toast.LENGTH_SHORT).show();
        FileInputStream fis = null;
        StringBuilder content = new StringBuilder();
        try
        {
            fis = new FileInputStream(f);
            byte[] b = new byte[fis.available() + 1];
            int readLength;
            do
            {
                readLength = fis.read(b);
                if(readLength > 0)
                {
                    content.append(new String(b, 0, readLength));
                }
            } while(readLength != -1);
        } catch(IOException e)
        {
            e.printStackTrace();
            Toast.makeText(getApplicationContext(), "Write Content to Extra Storage Failed", Toast.LENGTH_SHORT).show();
        } finally
        {
            if(fis != null)
            {
                try
                {
                    fis.close();
                } catch(IOException e)
                {
                    e.printStackTrace();
                }
                Toast.makeText(getApplicationContext(), "Write Content to Extra Storage Successfully", Toast.LENGTH_SHORT).show();
                textContent.setText(content.toString());
            }
        }
    }
}
