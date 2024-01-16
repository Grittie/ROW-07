package com.example.beveragebot;

import android.webkit.WebView;
import android.webkit.WebViewClient;

public class CameraFeed {

    private WebView webView;
    private static String BASE_URL;

    public CameraFeed(WebView webView) {
        this.webView = webView;
        initWebView();
    }

    private void initWebView() {
        webView.setWebViewClient(new WebViewClient());
        BASE_URL = "http://" + MainActivity.getUrl() + ":5000/video_feed";
        webView.loadUrl(BASE_URL);
    }
}

