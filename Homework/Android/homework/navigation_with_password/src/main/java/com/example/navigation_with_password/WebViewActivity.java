package com.example.navigation_with_password;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.Editable;
import android.text.method.KeyListener;
import android.view.KeyEvent;
import android.view.View;
import android.webkit.WebResourceRequest;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class WebViewActivity
        extends AppCompatActivity
{

    private EditText linkText;
    private Button openLink;
    private WebView webView;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_web_view);

        initView();
        bindEvent();
    }

    private void bindEvent()
    {
        webView.getSettings().setJavaScriptEnabled(true);
        webView.setWebViewClient(new WebViewClient() {
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url)
            {
                view.loadUrl(url);
                return true;
            }
        });
        openLink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                String link = linkText.getText().toString();
                if(link.length() == 0)
                {
                    return;
                }
                else if(link.length() < 4 || !link.contains("."))
                {
                    Toast.makeText(getApplicationContext(), "输入的网址有误", Toast.LENGTH_SHORT).show();
                    return;
                }
                else if(!(link.startsWith("http://") || link.startsWith("https://")))
                {
                    link = "http://" + link;
                }
                webView.loadUrl(link);
                linkText.setText("");
            }
        });
        linkText.setOnKeyListener(new View.OnKeyListener() {
            @Override
            public boolean onKey(View view, int i, KeyEvent keyEvent)
            {
                if(i == KeyEvent.KEYCODE_ENTER)
                    openLink.callOnClick();
                return false;
            }
        });
    }

    private void initView()
    {
        linkText = (EditText) findViewById(R.id.link);
        openLink = (Button) findViewById(R.id.openLink);
        webView = (WebView) findViewById(R.id.webView);
    }

    @Override
    public void onBackPressed()
    {
        if(linkText.getText().length() > 0)
            linkText.setText("");
        else
            super.onBackPressed();
    }
}
