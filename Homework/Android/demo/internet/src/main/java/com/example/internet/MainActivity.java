package com.example.internet;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import javax.net.ssl.HttpsURLConnection;

public class MainActivity
        extends AppCompatActivity
{

    private Button btnGet;
    private Button btnPost;
    private EditText editUrl;
    private EditText editPost;
    private TextView textResponse;
    private Button btnXML;
    private Button btnJSON;
    private Button btnDownload;
    private Button btnUpload;
    private ProgressBar progressBar;
    private ImageView imgView;

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
        btnGet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                final String url = editUrl.getText().toString();
                new AsyncTask<Void, Void, String>() {
                    @Override
                    protected String doInBackground(Void... voids)
                    {
                        return httpGet(url);
                    }

                    @Override
                    protected void onPostExecute(String result)
                    {
                        textResponse.setText(result);
                    }
                }.execute();
            }
        });
        btnPost.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                final String url = editUrl.getText().toString();
                final String param = editPost.getText().toString();
                new AsyncTask<Void, Void, String>() {
                    @Override
                    protected String doInBackground(Void... voids)
                    {
                        return httpPost(url, param);
                    }

                    @Override
                    protected void onPostExecute(String result)
                    {
                        textResponse.setText(result);
                    }
                }.execute();
            }
        });
        btnXML.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                textResponse.setText(parseXML(textResponse.getText().toString()));
            }
        });
        btnJSON.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                textResponse.setText(parseJSON(textResponse.getText().toString()));
            }
        });
        btnDownload.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                final Bitmap[] bitmap = {null};
                new AsyncTask<Void, Void, String>()
                {
                    @Override
                    protected String doInBackground(Void... voids)
                    {
                        bitmap[0] = download();
                        return null;
                    }

                    @Override
                    protected void onPostExecute(String s)
                    {
                        imgView.setImageBitmap(bitmap[0]);
                    }
                }.execute();
            }
        });
    }

    Bitmap download()
    {
        Bitmap bitmap = null;
        HttpURLConnection connection = null;
        try
        {
            URL url = new URL("https://bing.ioliu.cn/v1/rand?w=800&h=480");
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setConnectTimeout(8000);
            connection.setReadTimeout(8000);
            connection.connect();
            int status = connection.getResponseCode();
            if(status == 200)
            {
                InputStream is = connection.getInputStream();
                bitmap = BitmapFactory.decodeStream(is);
                is.close();
            }
        } catch(IOException e)
        {
            e.printStackTrace();
        } finally
        {
            if(connection != null)
                connection.disconnect();
        }
        return bitmap;
    }

    String parseJSON(String json)
    {
        StringBuffer strBuff = new StringBuffer();
        try
        {
            JSONObject jsonObject = new JSONObject(json);
            strBuff.append(jsonObject.getString("fun")).append(":").append(jsonObject.getString("callback"));
        } catch(JSONException e)
        {
            e.printStackTrace();
        }
        return strBuff.toString();
    }

    String parseXML(String xml)
    {
        StringBuffer strBuffer = new StringBuffer();
        try
        {
            XmlPullParserFactory factory = XmlPullParserFactory.newInstance();
            XmlPullParser parser = factory.newPullParser();
            parser.setInput(new StringReader(xml));
            int eventType = parser.getEventType();
            while(eventType != XmlPullParser.END_DOCUMENT)
            {
                String nodeName = parser.getName();
                switch(eventType)
                {
                    case XmlPullParser.START_TAG:
                    {
                        if(nodeName.equals("year"))
                        {
                            strBuffer.append(parser.nextText()).append("\n");
                        }
                        break;
                    }
                }
                eventType = parser.next();
            }
        } catch(XmlPullParserException | IOException e)
        {
            e.printStackTrace();
        }
        return strBuffer.toString();
    }

    String httpGet(String urlStr)
    {
        StringBuilder response = new StringBuilder();
        HttpURLConnection connection = null;
        try
        {
            URL url = new URL(urlStr);
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setConnectTimeout(8000);
            connection.setReadTimeout(5000);
            connection.connect();
            int status = connection.getResponseCode();
            if(status == 200)
            {
                InputStream is = connection.getInputStream();
                byte[] bytes = new byte[1024];
                int readLen;
                do
                {
                    readLen = is.read(bytes);
                    if(readLen > 0)
                    {
                        response.append(new String(bytes, 0, readLen));
                    }
                } while(readLen != -1);
                is.close();
                System.out.println(response.toString());
            }
        } catch(IOException e)
        {
            e.printStackTrace();
        } finally
        {
            if(connection != null)
                connection.disconnect();
        }
        return response.toString();
    }

    String httpPost(String urlStr, String postData)
    {
        StringBuilder response = new StringBuilder();
        HttpURLConnection connection = null;
        try
        {
            URL url = new URL(urlStr);
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Charset", "UTF-8");
            connection.setDoInput(true);
            connection.setDoOutput(true);
            connection.setUseCaches(false);
            OutputStream os = connection.getOutputStream();
            os.write(postData.getBytes());
            os.flush();
            os.close();
            connection.connect();
            int status = connection.getResponseCode();
            if(status == 200)
            {
                InputStream is = connection.getInputStream();
                byte[] bytes = new byte[1024];
                int readLen;
                do
                {
                    readLen = is.read(bytes);
                    if(readLen > 0)
                    {
                        response.append(new String(bytes, 0, readLen));
                    }
                } while(readLen != -1);
                is.close();
                System.out.println(response.toString());
            }
        } catch(IOException e)
        {
            e.printStackTrace();
        } finally
        {
            if(connection != null)
                connection.disconnect();
        }
        return response.toString();
    }


    private void initView()
    {
        btnGet = (Button) findViewById(R.id.btnGet);
        btnPost = (Button) findViewById(R.id.btnPost);
        btnXML = (Button) findViewById(R.id.btnXML);
        btnJSON = (Button) findViewById(R.id.btnJSON);
        btnDownload = (Button) findViewById(R.id.btnDownload);
        btnUpload = (Button) findViewById(R.id.btnUpload);
        editUrl = (EditText) findViewById(R.id.editUrl);
        editUrl.setText("https://chat.1sls.cn/test/xml.php");
        editPost = (EditText) findViewById(R.id.editPost);
        textResponse = (TextView) findViewById(R.id.textResponse);
        progressBar = (ProgressBar) findViewById(R.id.progressBar);
        imgView = (ImageView) findViewById(R.id.imageView);
    }
}
