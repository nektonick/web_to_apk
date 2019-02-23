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
 
        webView.loadUrl("https://example.com");
    }
 
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if ((keyCode == KeyEvent.KEYCODE_BACK) && this.webView.canGoBack()) {
            this.webView.goBack();
            return true;
        }
 
        return super.onKeyDown(keyCode, event);
    }
}
