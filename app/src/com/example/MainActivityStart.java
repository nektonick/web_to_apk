package com.example.helloandroid;
 
import android.os.Bundle;
import android.app.Activity;
import android.view.KeyEvent;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
 
public class MainActivity extends Activity {
 
    private WebView webView;
 
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        webView = (WebView) findViewById(R.id.webView);
 
        WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);
 
        WebViewClient webViewClient = new WebViewClient();
        webView.setWebViewClient(webViewClient);
	webView.getSettings().setBuiltInZoomControls(true);
	webView.getSettings().setDisplayZoomControls(false);
