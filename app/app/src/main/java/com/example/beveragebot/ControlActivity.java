package com.example.beveragebot;

import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class ControlActivity extends AppCompatActivity  implements MqttCallback{

    private Button pour, forward, left, right,back;
    private ImageButton info;
    private WebView webView;
    private CameraFeed cameraFeed;
    private MqttHandler mqttHandler;
    private TextView distanceTextView;
    private FrameLayout transparentOverlay;
    private static final String BROKER_URL = "tcp://" + MainActivity.getUrl() + ":1883";
    private static final String CLIENT_ID = "10";



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        webView = findViewById(R.id.webview);
        cameraFeed = new CameraFeed(webView);
        mqttHandler = new MqttHandler();
//        mqttHandler.connect(BROKER_URL, CLIENT_ID);
        // Subscribe to the "data" topic
//        mqttHandler.subscribe("data");
//        mqttHandler.subscribe("distance");


        forward = this.findViewById(R.id.button_forward);
        back= this.findViewById(R.id.button_back);
        left= this.findViewById(R.id.button_left);
        right= this.findViewById(R.id.button_right);
        pour = this.findViewById(R.id.button_pour);
        info = this.findViewById(R.id.button_info);
        transparentOverlay = this.findViewById(R.id.transparent_overlay);

//        receivedmessage = this.findViewById(R.id.receivedmessage);


        pour.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    publishMessage("direction","x" );
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    publishMessage("direction","s" );
                    SystemClock.sleep(10000);
                }
                return false;
            }
        });

        info.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                transparentOverlay.setVisibility(
                        transparentOverlay.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE
                );
                return false;
            }

        });


        forward.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    publishMessage("direction","f" );
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    publishMessage("direction","s" );
                    SystemClock.sleep(500);
                }
                return false;
            }
        });

        left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    publishMessage("direction","l" );
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    publishMessage("direction","s" );
                    SystemClock.sleep(500);
                }
                return false;
            }
        });

        right.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    publishMessage("direction","r" );
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    publishMessage("direction","s" );
                    SystemClock.sleep(500);
                }
                return false;
            }
        });

        back.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    publishMessage("direction","b" );
                }
                else if (event.getAction() == MotionEvent.ACTION_UP) {
                    publishMessage("direction","s" );
                    SystemClock.sleep(500);
                }
                return false;
            }
        });
    }



    private void publishMessage(String topic, String message) {
        mqttHandler.publish(topic, message);
    }

    private void subscribeToTopic(String topic) {
        mqttHandler.subscribe(topic);
    }
    @Override
    public void connectionLost(Throwable cause) {// Handle connection lost
        System.out.println("Connection lost. Trying to reconnect...");
        cause.printStackTrace();
    }


    public void onSubscribe(IMqttToken asyncActionToken) throws MqttException {
        Log.d("MqttHandler", "Subscribed to topic: " + asyncActionToken.getTopics()[0]);
    }


    @Override
    public void messageArrived(String topic, MqttMessage message) throws Exception {
        // Check if the received message is on the "distance" topic
        if ("distance".equals(topic)) {
            // Handle incoming message on the "distance" topic
            final String payload = new String(message.getPayload());

            // Update the UI or perform actions with the received "distance" message
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    // Display the received "distance" message in the UI (for example, in a TextView)
                    if (distanceTextView != null) {
                        distanceTextView.setText("Distance: " + payload);
                    } else {
                        Log.e("MainActivity", "distanceTextView is null");
                    }
                }
            });
        }
    }
    @Override
   public void deliveryComplete(org.eclipse.paho.client.mqttv3.IMqttDeliveryToken token) {
        // Handle delivery complete
    }
}
