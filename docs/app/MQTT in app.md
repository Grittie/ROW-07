# MQTT Implementation in Android App

This file describes how to use MQTT in Android Java for both publishing (publish) and subscribing (subscribe)

## Step 1: Add Paho MQTT Library to your Project

Add the following dependencies to your build.gradle file:

```bash
implementation 'org.eclipse.paho:org.eclipse.paho.client.mqttv3:1.2.5'
implementation 'org.eclipse.paho:org.eclipse.paho.android.service:1.1.1'
```


## Step 2: Add Internet Permission
Ensure that your AndroidManifest.xml includes the following permission:


```bash
<uses-permission android:name="android.permission.INTERNET" />
```


## Step 3: Create an MQTT class
Create an MQTT service class that will handle the MQTT connection and operations.
```bash
import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class MqttHandler{
    private MqttAndroidClient mqttAndroidClient;

    public void connect(String brokerUrl, String clientId, String username, String password, MqttCallback mqttCallback) {
        String serverUri = "tcp://" + brokerUrl + ":1883";
        mqttAndroidClient = new MqttAndroidClient(App.getContext(), serverUri, clientId);

        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setCleanSession(true);
        mqttConnectOptions.setUserName(username);
        mqttConnectOptions.setPassword(password.toCharArray());

        try {
            IMqttToken token = mqttAndroidClient.connect(mqttConnectOptions);
            token.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // Connection success
                    mqttAndroidClient.setCallback(mqttCallback);
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    // Connection failure
                    exception.printStackTrace();
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void disconnect() {
        try {
            mqttAndroidClient.disconnect();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void publish(String topic, String message) {
        try {
            MqttMessage mqttMessage = new MqttMessage(message.getBytes());
            mqttAndroidClient.publish(topic, mqttMessage);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void subscribe(String topic) {
        try {
            mqttAndroidClient.subscribe(topic, 1); // QoS 1
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

## Step 4: Use the MQTT class in Your Activity
In your activity, you can use the Mqtt class to connect, publish, and subscribe


```bash
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class MainActivity extends AppCompatActivity {

    private MqttHandler mqttHandler;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        MqttHandler = new MqttHandler ();

        // Connect to MQTT broker
       MqttHandler.connect("your_broker_address", "your_client_id", "your_username", "your_password", new MqttCallbackHandler());

        // Subscribe to a topic
       MqttHandler.subscribe("your_topic");

        // Publish a message
        MqttHandler.publish("your_topic", "Hello, MQTT!");

        // Disconnect when your activity is destroyed
        // Override onDestroy() method if necessary
    }

    // Implement a MqttCallbackHandler to handle incoming messages
    private class MqttCallbackHandler implements MqttCallback {
        @Override
        public void connectionLost(Throwable cause) {
            // Handle connection lost
            cause.printStackTrace();
        }

        @Override
        public void messageArrived(String topic, MqttMessage message) throws Exception {
            // Handle incoming messages
            String payload = new String(message.getPayload());
            System.out.println("Received message on topic '" + topic + "': " + payload);
        }

        @Override
        public void deliveryComplete(IMqttDeliveryToken token) {
            // Handle message delivery completion
        }
    }
}
```