package com.example.beveragebot;

// MainActivity.java

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.media.MediaPlayer;
import android.util.Log;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class MainActivity extends AppCompatActivity  {

    private Button buttonStart;

    private MqttHandler mqttHandler;
    private static final String BROKER_URL = "tcp://" + MainActivity.getUrl() + ":1883";
    private static final String CLIENT_ID = "10";
    private static final String URL = "192.168.161.203";

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.homescreen);

        buttonStart = this.findViewById(R.id.StartButton);



        // Create an instance of MqttHandler
        mqttHandler = new MqttHandler();

      // Connect to MQTT broker (you need to replace these with your actual broker details)
//        mqttHandler.connect(BROKER_URL, CLIENT_ID);
        // Subscribe to the "data" topic
//        mqttHandler.subscribe("data");






        final MediaPlayer bp = MediaPlayer.create(this, R.raw.can_open);

        buttonStart.setOnClickListener(view -> {
            bp.start();
            Intent intent = new Intent(this, ControlActivity.class);
            startActivity(intent);
        });

    }

    public static String getUrl() {
        return URL;
    }

//    @Override
//    public void connectionLost(Throwable cause) {
//        // Handle connection lost
//        System.out.println("Connection lost. Trying to reconnect...");
//        cause.printStackTrace();
//    }
//
//    @Override
//    public void messageArrived(String topic, MqttMessage message) throws Exception {
//        // Check if the received message is on the "data" topic
//        if ("data".equals(topic)) {
//            // Handle incoming message on the "data" topic
//            final String payload = new String(message.getPayload());
//
//            // Update the UI or perform actions with the received "data" message
//            runOnUiThread(new Runnable() {
//                @Override
//                public void run() {
//                    // Display the received "data" message in the UI (for example, in a TextView)
//                    // Make sure you have a TextView with the ID "receivedMessageTextView" in your layout
//                    if (receivedMessageTextView != null) {
//                        receivedMessageTextView.setText("Received Data: " + payload);
//                    } else {
//                        Log.e("MainActivity", "receivedMessageTextView is null");
//                    }
//                }
//            });
//        }
//    }
//
//    @Override
//    public void deliveryComplete(org.eclipse.paho.client.mqttv3.IMqttDeliveryToken token) {
//        // Handle delivery complete
//    }

    @Override
    protected void onDestroy() {
        // Disconnect from the MQTT broker when the activity is destroyed
        mqttHandler.disconnect();
        super.onDestroy();
    }
}
