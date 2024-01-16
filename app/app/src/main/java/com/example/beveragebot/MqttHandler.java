package com.example.beveragebot;


import android.app.Activity;
import android.util.Log;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MqttHandler  implements MqttCallback{

    private MqttClient client;

    public void connect(String brokerUrl, String clientId) {
        try {
            // Set up the persistence layer
            MemoryPersistence persistence = new MemoryPersistence();

            // Initialize the MQTT client
            client = new MqttClient(brokerUrl, clientId, persistence);

            // Set up the connection options
            MqttConnectOptions connectOptions = new MqttConnectOptions();
            connectOptions.setCleanSession(true);

            // Connect to the broker
            client.connect(connectOptions);


        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    public void disconnect() {
//        try {
//            client.disconnect();
//        } catch (MqttException e) {
//            e.printStackTrace();
//        }


    }

    public void publish(String topic, String message) {
        try {
            MqttMessage mqttMessage = new MqttMessage(message.getBytes());
            client.publish(topic, mqttMessage);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }




    public void subscribe(String topic) {
        try {
            client.subscribe(topic);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }




    public void setCallback(MqttCallback callback) {
        client.setCallback(callback);
    }

    @Override
    public void connectionLost(Throwable cause) {
        // Handle connection lost
        System.out.println("Connection lost. Trying to reconnect...");
        cause.printStackTrace();
    }



    @Override
    public void messageArrived(String topic, MqttMessage message) throws Exception {
        // Handle incoming messages

        // Check if the topic is the one you are interested in (e.g., "data")
        if ("data".equals(topic)) {
            String payload = new String(message.getPayload());

            // Print the received message
            System.out.println("Received message on topic 'data': " + payload);


        }


    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken token) {

    }
}
