# Integrating Video Stream into Android App

To display the video stream from Flask in an Android app using Android Studio, we use a WebView component to load the stream's URL. Below is a simple class `CameraFeed` in Java that encapsulates this functionality.

## CameraFeed Class

```java
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
        // Set a WebViewClient to handle navigation within the WebView
        webView.setWebViewClient(new WebViewClient());

        // Construct the base URL for the video stream
        BASE_URL = "http://" + MainActivity.getUrl() + ":5000/video_feed";

        // Load the video stream URL into the WebView
        webView.loadUrl(BASE_URL);
    }
}
```

## Integration Steps

To integrate the video stream into your Android app using the `CameraFeed` class:

1. **Create a WebView in Your Layout:**
   - In your XML layout file, add a WebView element where you want the video stream to be displayed.
   ```xml
   <WebView
       android:id="@+id/webView"
       android:layout_width="match_parent"
       android:layout_height="match_parent"/>
   ```

2. **Initialize CameraFeed in Your Activity:**
   - In your activity where you want to display the video stream, initialize the `CameraFeed` class.
   ```java
   public class YourActivity extends AppCompatActivity {

       @Override
       protected void onCreate(Bundle savedInstanceState) {
           super.onCreate(savedInstanceState);
           setContentView(R.layout.activity_your);

           // Get the WebView from the layout
           WebView webView = findViewById(R.id.webView);

           // Initialize CameraFeed and load the video stream
           new CameraFeed(webView);
       }
   }
   ```

3. **Ensure Internet Permission:**
   - In your AndroidManifest.xml, make sure you have the internet permission.
   ```xml
   <uses-permission android:name="android.permission.INTERNET" />
   ```

4. **Run Your App:**
   - Build and run your Android app in Android Studio. The video stream from the Flask server should now be displayed in the WebView.

## Note
- Make sure your Android device and the computer running the Flask server are on the same network.
- Replace `activity_your` with the actual name of your activity layout file.

This integration allows your Android app to receive and display the real-time video stream from the Flask server using the WebView component.

## Related Documentation

For additional information and documentation, refer to the following related documents:

- [Streaming ](../pi/streaming.md)
- [Computer Vision](../pi/computervision.md)